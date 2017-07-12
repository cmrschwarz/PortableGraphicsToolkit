#include <pgt/window/engine.h>
#include "SdlApp.h"
#include <GL/glew.h>
#include <pgt/io/logger/logger.h>
#include <FreeImage/FreeImage.h>
#include <pgt/io/vfs/VirtualFileSystem.h>
#include <pgt/io/vfs/OSDirectory.h>
#include <pgt/utils/debug/MessageBoxes.h>
#include <pgt/graphics/plattform/interface/IRenderingContext.h>
#include "SdlWindowEventHoudshold.h"
#include <FreeImage/FreeImage.h>
#include <SDL2/SDL.h>
namespace pgt {
    namespace plattform {
        // FWD
        decltype(SdlApp::_instances) SdlApp::_instances;
        decltype(SdlApp::_initialized) SdlApp::_initialized = false;
        decltype(SdlApp::_window_creation_lock) SdlApp::_window_creation_lock;

        // CTOR
        SdlApp::SdlApp()
            : IApp(),
              _event_based(false),
              _running(false),
              _thread_id(std::this_thread::get_id())
        {
            std::lock_guard<std::mutex> lg(_window_creation_lock);
            // pointer _tls_app gets set AFTER Costruction
            // This ensures only one App instance per Thread
            PGT_DEBUG_ASSERT(pgt::engine::isAppInitialized() == false,
                            "There can only ever be one app per thread");

            // TODO: this is a race condition
            if (_instances.size() == 0) {
                initSDL();
#ifdef FREEIMAGE_LIB
                FreeImage_Initialise();
#endif
            }
            _instances.push_back(this);
            PGT_LOG_DEBUG("SDL App Created");
        }

        // DTOR
        SdlApp::~SdlApp()
        {
            std::lock_guard<std::mutex> lg(_window_creation_lock);
            for (auto it = _instances.begin(); it != _instances.end(); ++it) {
                if (*it == this) {
                    _instances.erase(it);
                    break;
                }
            }

            // TODO: this is a race condition6
            if (_instances.size() == 0) {
                SDL_Quit();
#ifdef FREEIMAGE_LIB
                FreeImage_DeInitialise();
#endif
                _initialized = false;
            }
            PGT_LOG_DEBUG("SDL App Destroyed");
        }


        // PUBLIC
        bool SdlApp::isRunning() const
        {
            return _running;
        }

        void SdlApp::run()
        {
            try {
                _running = true;
                while (_running && _window_event_households.size() > 0) {
                    pollEvents();
                    if (!_running) break;
                    // DONT make this use iterators. Would be UB if somebody
                    // added a window
                    for (size_t i = 0; i < _window_event_households.size();
                         i++) {
                        auto& hh = *_window_event_households[i];
                        auto& window = *hh.getUserWindow();
                        handleEventsForWindow(hh);
                        if (window.shouldClose()) {
                            engine::getApp().setRenderingContext(
                                window.getRenderingContext());
                            window.internal_destroy();
                            window.deleteMe();  // for MEH. TODO: evaluate
                            delete &hh;
                            _window_event_households.erase(
                                _window_event_households.begin() + i);
                            break;
                        }

                        if (!_running) break;
                        window.internal_update();
                        if (!_running) break;
                    }
                }
                _running = false;
                PGT_LOG_INFO("Terminating...");
                for (int i = 0; i < _window_event_households.size(); i++) {
                    auto* hh = _window_event_households.back();
                    auto* win = hh->getUserWindow();
                    // all windows that are still in the list are open by
                    // defenition
                    hh->getUserWindow()->close();
                    win->deleteMe();  // for MEH
                    delete hh;
                    // has to be done  because closing could read from the
                    // households
                    _window_event_households.pop_back();
                }
                if (_terminated) {
                    engine::internal::terminateAppCallback(this);
                }
                PGT_LOG_INFO("SdlApp ended. All Windows CLosed");
            }
            catch (std::exception& ex) {
                messageBox(ex.what());
            }
        }
        // TODO: make a diagramm for this and check correctness
        void SdlApp::terminate()
        {
            _terminated = true;
            if (_running) {
                SDL_Event* e = new SDL_Event();
                e->type = _sdl_user_event_terminate_app;
                e->user.data2 = e;
                SDL_PushEvent(e);
                requestEventBased(false);
            }
            else {
                engine::internal::terminateAppCallback(this);
            }
        }

        void SdlApp::setRenderingContext(IRenderingContext& rc)
        {
            if (_rendering_context != &rc) {
                _rendering_context = &rc;
                rc.setContextCurrent();
                PGT_LOG_DEBUG(
                    "Made Rendering Context Current from Window: \"%s\"",
                    _rendering_context->getWindow().getTitle().c_str());
            }
        }

        IRenderingContext& SdlApp::getRenderingContext() const
        {
            PGT_DEBUG_ASSERT(_rendering_context, "No Valid Rendering Context");
            return *_rendering_context;
        }

        // private
        void SdlApp::initSDL()
        {
            // INIT
            _initialized = true;
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK),
            //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            PGT_ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "Failed to init SDL: %s",
                      SDL_GetError());

            // PRINT VERSION
            SDL_version compiled, linked;
            SDL_VERSION(&compiled);
            SDL_GetVersion(&linked);
            if (compiled.major == linked.major &&
                compiled.minor == linked.minor) {
                PGT_LOG_INFO("SDL vcomp %i.%i.%i vlink %i.%i.%i", compiled.major,
                            compiled.minor, compiled.patch, linked.major,
                            linked.minor, linked.patch);
            }
            else {
                PGT_LOG_WARN("SDL vcomp %i.%i.%i vlink %i.%i.%i", compiled.major,
                            compiled.minor, compiled.patch, linked.major,
                            linked.minor, linked.patch);
            }

            // TODO: make this thread safe
            SDL_SetEventFilter(&eventFilter, nullptr);
            _sdl_user_event_terminate_app = SDL_RegisterEvents(1);
            PGT_ASSERT(_sdl_user_event_terminate_app != -1,
                      "SDL Error: No User Events available");
            PGT_LOG_INFO("Initialized SdlApp");
        }
        void SdlApp::initGLEW()
        {
            glewExperimental = GL_TRUE;
            int err = glewInit();
            PGT_ASSERT(err == GLEW_OK, "Failed to init GLEW: %i", err);
            SDL_SetEventFilter(&eventFilter, nullptr);
            const char* gl_version =
                reinterpret_cast<const char*>(glGetString(GL_VERSION));
            PGT_LOG_INFO("OpenGL %s", gl_version);
            PGT_LOG_INFO("GLEW %i.%i.%i", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR,
                        GLEW_VERSION_MICRO);
        }

        void SdlApp::createWindow(SdlWindow* win, const sdl_window_data& data)
        {
            _event_based = false;
            std::lock_guard<std::mutex> lg(_window_creation_lock);
            int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
            if (data.fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
            int x = (data.pos_x == SdlWindow::DEFAULT) ? SDL_WINDOWPOS_UNDEFINED
                                                       : data.pos_x;
            int y = (data.pos_y == SdlWindow::DEFAULT) ? SDL_WINDOWPOS_UNDEFINED
                                                       : data.pos_y;
            if (data.fullscreen && (data.width == SdlWindow::DEFAULT ||
                                    data.height == SdlWindow::DEFAULT)) {
                // TODO: improve
                SDL_DisplayMode disp_mode;
                SDL_GetCurrentDisplayMode(0, &disp_mode);
                data.width = disp_mode.w;
                data.height = disp_mode.h;
            }
            // TODO: improve window creation
            SDL_Window* sdl_window = SDL_CreateWindow(
                data.title, x, y, data.width, data.height, flags);
            PGT_ASSERT(sdl_window, "Failed to create Window");
            *data.created_window = sdl_window;
            SDL_GetWindowSize(sdl_window, &data.width, &data.height);
            SDL_GetWindowPosition(sdl_window, &data.pos_x, &data.pos_y);
            SdlWindowEventHousehold* weh =
                new SdlWindowEventHousehold(win, sdl_window);
            _window_event_households.push_back(weh);
            if (data.gl_context != nullptr) {
                *data.gl_context = SDL_GL_CreateContext(sdl_window);
                PGT_ASSERT(*data.gl_context, "Failed to create a GL Context");
                SDL_GL_MakeCurrent(sdl_window, *data.gl_context);
                initGLEW();
            }
            engine::internal::checkGLErrors("GL Error during window creation");
        }

        int SdlApp::eventFilter(void* userdata, SDL_Event* event)
        {
            if (event->type == SDL_WINDOWEVENT) {
                if (event->window.event == SDL_WINDOWEVENT_RESIZED
                    /*||event->window.event == SDL_WINDOWEVENT_MOVED*/) {
                    SdlWindowEventHousehold* hh = nullptr;
                    SdlApp* app = nullptr;
                    for (auto it = _instances.begin(); it != _instances.end();
                         ++it) {
                        hh = (*it)->getEventHouseHouseHoldFromID(
                            event->window.windowID);
                        if (hh != nullptr) {
                            app = *it;
                            break;
                        }
                    }
                    //  if (hh == nullptr) return;
                    if (app->_thread_id != std::this_thread::get_id()) {
                        return 1;
                    }
                    hh->pushEvent(*event);
                    app->handleEventsForWindow(*hh);
                    return 0;
                }
            }
            return 1;
        }

        int SdlApp::pollSdlEvent(SDL_Event* e, bool wait)
        {
            if (wait) {
                return SDL_WaitEvent(e);
            }
            else {
                return SDL_PollEvent(e);
            }
        }
        void SdlApp::pollEvents()
        {
            SDL_Event e;
            SdlWindowEventHousehold* hh;
            bool ec = 0;
            while (pollSdlEvent(&e, _event_based && ec == false) != 0) {
                ec = true;
                switch (e.type) {
                case SDL_WINDOWEVENT:
                    hh = getEventHouseHouseHoldFromID(e.window.windowID);
                    if (hh != nullptr) hh->pushEvent(e);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    hh = getEventHouseHouseHoldFromID(e.button.windowID);
                    if (hh != nullptr) hh->pushEvent(e);
                    break;
                case SDL_MOUSEMOTION:
                    hh = getEventHouseHouseHoldFromID(e.motion.windowID);
                    if (hh != nullptr) hh->pushEvent(e);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    hh = getEventHouseHouseHoldFromID(e.key.windowID);
                    if (hh != nullptr) hh->pushEvent(e);
                    break;
                case SDL_MOUSEWHEEL:
                    hh = getEventHouseHouseHoldFromID(e.wheel.windowID);
                    if (hh != nullptr) hh->pushEvent(e);
                default: {
                    if (e.type == _sdl_user_event_terminate_app) {
                        delete (SDL_Event*)e.user.data2;
                        _running = false;
                        return;
                    }
                    else {
                        for (auto it = _window_event_households.begin();
                             it != _window_event_households.end(); ++it) {
                            (*it)->pushEvent(e);
                        }
                        break;
                    }
                }
                }
            }
        }

        void SdlApp::handleEventsForWindow(SdlWindowEventHousehold& hh)
        {
            SdlWindow& window = *hh.getUserWindow();
            if (window._dirty_state) return;
            setRenderingContext(window.getRenderingContext());
            SDL_Event* evnt_p;
            SDL_Event ev;
            while ((evnt_p = hh.peakEvent())) {
                // we copy to avoid eg. the msgbox bug caused by this loop being
                // entered while an older event it is still on the stack and
                // being processed
                ev = *evnt_p;
                hh.popEvent();
                switch (ev.type) {
                case SDL_WINDOWEVENT: {
                    switch (ev.window.event) {
                    case SDL_WINDOWEVENT_RESIZED: {
                        ResizeEvent r(vec2i(ev.window.data1, ev.window.data2));
                        window.raiseOnResize(r);
                        window.internal_update();
                        break;
                    }
                    case SDL_WINDOWEVENT_MOVED: {
                        MoveEvent r(ev.window.data1, ev.window.data2);
                        window.raiseOnMove(r);
                        window.internal_update();
                        break;
                    }
                    case SDL_WINDOWEVENT_CLOSE: {
                        window.raiseOnClosing();
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_GAINED: {
                        window.raiseOnFocusGained();
                        break;
                    }
                    case SDL_WINDOWEVENT_FOCUS_LOST: {
                        window.raiseOnFocusLost();
                        break;
                    }
                    default:
                        break;
                    }
                    break;
                }
                case SDL_MOUSEMOTION: {
                    MouseMoveEvent r(ev.motion.x, ev.motion.y, ev.motion.xrel,
                                     ev.motion.yrel);
                    window.raiseOnMouseMoved(r);
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN: {
                    PGT_KEYS btn;
                    if (ev.button.button == SDL_BUTTON_LEFT)
                        btn = PGT_KEYS::MBUTTON_LEFT;
                    else if (ev.button.button == SDL_BUTTON_MIDDLE)
                        btn = PGT_KEYS::MBUTTON_MIDDLE;
                    else if (ev.button.button == SDL_BUTTON_RIGHT)
                        btn = PGT_KEYS::MBUTTON_RIGHT;
                    else
                        btn = PGT_KEYS::KEY_UNKNOWN;
                    if (ev.button.state == SDL_PRESSED) {
                        MouseButtonDownEvent r(ev.button.x, ev.button.y, btn);
                        window.raiseOnMouseButtonDown(r);
                    }
                    else {
                        MouseButtonUpEvent r(ev.button.x, ev.button.y, btn);
                        window.raiseOnMouseButtonUp(r);
                    }
                    break;
                }
                case SDL_KEYDOWN: {
                    auto ke = KeyDownEvent(convertKeyCode(ev.key.keysym.sym),
                                           ev.key.repeat,
                                           (ev.key.keysym.mod & KMOD_SHIFT),
                                           (ev.key.keysym.mod & KMOD_CTRL),
                                           (ev.key.keysym.mod & KMOD_ALT));
                    window.raiseOnKeyDown(ke);
                    break;
                }
                case SDL_KEYUP: {
                    auto ke = KeyUpEvent(convertKeyCode(ev.key.keysym.sym),
                                         (ev.key.keysym.mod & KMOD_SHIFT),
                                         (ev.key.keysym.mod & KMOD_CTRL),
                                         (ev.key.keysym.mod & KMOD_ALT));
                    window.raiseOnKeyUp(ke);
                    break;
                }
                case SDL_MOUSEWHEEL: {
                    int scroll = -ev.wheel.y;  // i prefer down being positive
                    if (ev.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)
                        scroll = -scroll;
                    auto se = MouseScrollEvent(scroll);
                    window.raiseOnMouseScrolled(se);
                    break;
                }
                default:
                    break;
                }
            }
        }

        void SdlApp::requestEventBased(bool val)  // TODO: find better name
        {
            if (val == false)
                _event_based = false;
            else {
                _event_based = true;
                for (auto it = _window_event_households.begin();
                     it != _window_event_households.end(); ++it) {
                    if ((!(*it)->getUserWindow()->shouldClose()) &&
                        (*it)->getUserWindow()->prefersEventBased() == false) {
                        _event_based = false;
                    }
                }
            }
        }

        bool SdlApp::isEventBased() const
        {
            return _event_based;
        }

        SdlWindowEventHousehold* SdlApp::getEventHouseHouseHoldFromID(
            uint32_t id)
        {
            for (auto it = _window_event_households.begin();
                 it != _window_event_households.end(); ++it) {
                if ((*it)->getWindowID() == id) return (*it);
            }
            return nullptr;
        }

        PGT_KEYS SdlApp::convertKeyCode(int sdlk)
        {
            if (sdlk >= SDLK_0 && sdlk <= SDLK_9)
                return (PGT_KEYS)(KEY_0 + (sdlk - SDLK_0));
            if (sdlk >= SDLK_F1 && sdlk <= SDLK_F24)
                return (PGT_KEYS)(KEY_F1 + (sdlk - SDLK_F1));
            if (sdlk >= SDLK_a && sdlk <= SDLK_z)
                return (PGT_KEYS)(KEY_A + (sdlk - SDLK_a));
            switch (sdlk) {
            case SDLK_LSHIFT:
                return KEY_SHIFT_L;
            case SDLK_RSHIFT:
                return KEY_SHIFT_R;
            case SDLK_LCTRL:
                return KEY_CTRL_L;
            case SDLK_RCTRL:
                return KEY_CTRL_R;
            case SDLK_LALT:
                return KEY_ALT_L;
            case SDLK_RALT:
                return KEY_ALT_R;
            case SDLK_KP_ENTER:
                return KEY_ENTER;
            case SDLK_ESCAPE:
                return KEY_ESCAPE;
            case SDLK_SPACE:
                return KEY_SPACE;
            case SDLK_PLUS:
                return KEY_PLUS;
            case SDLK_MINUS:
                return KEY_MINUS;
            case SDLK_BACKSPACE:
                return KEY_BACKSPACE;
            default:
                return KEY_UNKNOWN;
            }
        }
    }
}