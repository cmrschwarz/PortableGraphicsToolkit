#include "GlfwManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <pgt/graphics/window/events/Inputmanager.h>
#include <pgt/graphics/window/plattform/glfw/GlfwWindow.h>
#include <pgt/maths/maths.h>
#include <FreeImage/FreeImage.h>
namespace pgt {
#define PGT_DECL(var) decltype(GlfwManager::var) GlfwManager::var
    PGT_DECL(_cancel_x_render_requests);
    PGT_DECL(_requires_x_render_pass);
    PGT_DECL(_x_render_path_lock);
    PGT_DECL(_x_render_path_executed);
    PGT_DECL(_window_map);
    PGT_DECL(_window_map_lock);
    PGT_DECL(_command_queue);
    PGT_DECL(_command_queue_lock);
    PGT_DECL(_command_execured);
    PGT_DECL(_running);
    PGT_DECL(_polling_thread);
#undef PGT_DECL
}
namespace pgt {
    GLFWwindow* GlfwManager::init(const window_data& data)
    {
        _cancel_x_render_requests = false;
        _requires_x_render_pass = nullptr;
        _running = true;
        _polling_thread = std::thread(pollingThread);
        GLFWwindow* window = createWindow(data);
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        PGT_ASSERT(glewInit() == GLEW_OK, "Failed to init GLEW");
        return window;
    }
    void GlfwManager::quit()
    {
        _running = false;
        for (auto it = _window_map.begin(); it != _window_map.end(); ++it) {
            delete (it->second);
        }
        _window_map.clear();
        _polling_thread.join();
    }

    void GlfwManager::executeOnPollThread(CommandFunc func,
                                          bool wait /*= false*/)
    {
        static bool* NOT_TRUE = new bool(false);  // cleaned up on app exit
        if (wait == false) {
            std::lock_guard<std::mutex> lg(_command_queue_lock);
            _command_queue.push_back(command(func, NOT_TRUE));
            return;
        }
        else {
            stopXRenderRequests();
            std::unique_lock<std::mutex> ul(_command_queue_lock);
            bool* not_executed_yet = new bool(true);
            _command_queue.push_back(command(func, not_executed_yet));
            _command_execured.wait(ul, [not_executed_yet] {
                return (*not_executed_yet == false);
            });
            delete not_executed_yet;
            resumeXRenderRequests();
        }
    }


    GLFWwindow* GlfwManager::createWindow(const window_data& data)
    {
        if (!_running) {
            return init(data);
        }
        GLFWwindow* created_window;
        executeOnPollThread(
            [&data, &created_window] {
                return makeWindow(data, &created_window);
            },
            true);
        return created_window;
    }

    pgt::GlfwWindowEventHousehold& GlfwManager::getWindowEventHousehold(
        GLFWwindow* w)
    {
        return *_window_map[w];
    }

    void GlfwManager::lockEventQueue()
    {
        _window_map_lock.lock();
    }

    void GlfwManager::unlockEventQueue()
    {
        _window_map_lock.unlock();
    }


    void GlfwManager::pollingThread()
    {
        glfwInit();
        glfwSetErrorCallback(error_callback);
        while (_running) {
            glfwPollEvents();
            performCommands();
        }
        glfwTerminate();
    }
    void GlfwManager::performCommands()
    {
        if (_command_queue.size() > 0) {  // TODO: evaluate if this is UB
            _command_queue_lock.lock();
            bool somebody_waking_up = false;
            for (size_t i = 0; i < _command_queue.size(); i++) {
                command& c = _command_queue[i];
                (c.func)();
                if (*c.commander_should_wait) {
                    *c.commander_should_wait = false;
                    somebody_waking_up = true;
                }
            }
            _command_queue.clear();
            _command_queue_lock.unlock();
            if (somebody_waking_up) _command_execured.notify_all();
        }
    }


    void GlfwManager::makeWindow(const window_data& request, GLFWwindow** w)
    {
        std::lock_guard<std::mutex> lg(_window_map_lock);
        if (request.fullscreen) {
            if (*request.width == window_creation_hints::DEFAULT &&
                *request.height == window_creation_hints::DEFAULT) {
                const GLFWvidmode* vm =
                    glfwGetVideoMode(glfwGetPrimaryMonitor());
                *request.width = vm->width;
                *request.height = vm->height;
            }
        }
        GLFWwindow* created_window = glfwCreateWindow(
            *request.width, *request.height, request.title,
            ((request.fullscreen) ? glfwGetPrimaryMonitor() : nullptr),
            request.context_share);
        if (request.pos_x != nullptr) {
            if (*request.pos_x == window_creation_hints::DEFAULT &&
                *request.pos_y == window_creation_hints::DEFAULT) {
                glfwGetWindowPos(created_window, request.pos_x, request.pos_y);
            }
            else {
                glfwSetWindowPos(created_window, *request.pos_x,
                                 *request.pos_y);
            }
        }
        glfwMakeContextCurrent(created_window);
        glfwSwapInterval(0);
        glfwMakeContextCurrent(nullptr);
        glfwSetKeyCallback(created_window, key_callback);
        glfwSetCursorPosCallback(created_window, cursor_position_callback);
        glfwSetMouseButtonCallback(created_window, mouse_button_callback);
        glfwSetWindowCloseCallback(created_window, window_close_callback);
        glfwSetWindowSizeCallback(created_window, window_size_callback);
        glfwSetWindowPosCallback(created_window, window_pos_callback);
        glfwSetWindowRefreshCallback(created_window, window_refresh_callback);
        glfwSetFramebufferSizeCallback(created_window,
                                       window_framebuffer_size_callback);
        // for now share means replace
        if (request.context_share != nullptr) {
            glfwDestroyWindow(request.context_share);
            // hijack household to preserve mutex

            GlfwWindowEventHousehold* h =
                &getWindowEventHousehold(request.context_share);
            h->_events.clear();
            // change to new key
            _window_map.erase(request.context_share);
            _window_map.insert(std::make_pair(created_window, h));
            h->_user_window = request.user_window;
        }
        else {
            GlfwWindowEventHousehold* h = new GlfwWindowEventHousehold();
            _window_map.insert(std::make_pair(created_window, h));
            h->_user_window = request.user_window;
        }
        *w = created_window;
    }

    void GlfwManager::key_callback(GLFWwindow* window, int key, int scancode,
                                   int action, int mods)
    {
        std::lock_guard<std::mutex> lg(_window_map_lock);
        auto& hh = getWindowEventHousehold(window);
        PGT_KEY kc = InputManager::convertGlfwKeycode(key, scancode, mods);
        bool repeat = (action == GLFW_REPEAT);
        bool down = (action == GLFW_PRESS || action == GLFW_REPEAT);
        bool shift = (mods & GLFW_MOD_SHIFT) != 0;
        bool ctrl = (mods & GLFW_MOD_CONTROL) != 0;
        bool alt = (mods & GLFW_MOD_ALT) != 0;
        hh._events.push_back(new KeyEvent(kc, down, repeat, shift, ctrl, alt));
    }

    void GlfwManager::cursor_position_callback(GLFWwindow* window, double xpos,
                                               double ypos)
    {
        std::lock_guard<std::mutex> lg(_window_map_lock);
        auto& hh = getWindowEventHousehold(window);
        // relative will be set on poll when you have access to
        // the input manager
        // TODO: investigate if pos is relative to the window pos
        // decide on internal convention
        hh._events.push_back(new MouseMoveEvent((int)std::round(xpos),
                                                (int)std::round(ypos), 0, 0));
    }

    void GlfwManager::mouse_button_callback(GLFWwindow* window, int button,
                                            int action, int mods)
    {
        std::lock_guard<std::mutex> lg(_window_map_lock);
        auto& hh = getWindowEventHousehold(window);
        PGT_KEY kc = InputManager::convertGlfwKeycode(button, 0, mods);
        bool down = (action == GLFW_PRESS);
        double x, y;
        // TODO: technically not safe by the documentation, switch to other
        // system.
        // BUT IT WORKS :(((
        glfwGetCursorPos(window, &x, &y);
        hh._events.push_back(new MouseClickEvent((int)std::round(x),
                                                 (int)std::round(y), kc, down));
    }

    void GlfwManager::window_close_callback(GLFWwindow* window)
    {
        std::lock_guard<std::mutex> lg(_window_map_lock);
        auto& hh = getWindowEventHousehold(window);
        hh._events.push_back(new WindowCloseEvent());
    }

    void GlfwManager::window_pos_callback(GLFWwindow* window, int xpos,
                                          int ypos)
    {
        std::lock_guard<std::mutex> lg(_window_map_lock);
        auto& hh = getWindowEventHousehold(window);
        hh._events.push_back(new WindowMoveEvent(xpos, ypos));
    }
    GlfwWindow* GlfwManager::requiresExtraRenderPass()
    {
        return _requires_x_render_pass;
    }

    void GlfwManager::performedExtraRenderPass()
    {
        _requires_x_render_pass = nullptr;
        _x_render_path_executed.notify_one();
    }
    void GlfwManager::requestXRenderPath(GlfwWindowEventHousehold& hh)
    {
        if (_cancel_x_render_requests) return;
        if (!hh._user_window->isNiceResizeEnabled()) return;
        std::unique_lock<std::mutex> ul(_x_render_path_lock);
        if (_cancel_x_render_requests) return;
        _requires_x_render_pass = hh._user_window;
        _x_render_path_executed.wait(ul, [] {
            return (_requires_x_render_pass == (GlfwWindow*)nullptr);
        });
    }

    void GlfwManager::stopXRenderRequests()
    {
        // should be safe ~.~
        _cancel_x_render_requests = true;
        _requires_x_render_pass = nullptr;
        _x_render_path_executed.notify_one();
    }

    void GlfwManager::resumeXRenderRequests()
    {
        _cancel_x_render_requests = false;
    }

    void GlfwManager::window_size_callback(GLFWwindow* window, int width,
                                           int height)
    {
        glfwGetFramebufferSize(window, &width, &height);
        _window_map_lock.lock();
        auto& hh = getWindowEventHousehold(window);
        hh._events.push_back(new WindowResizeEvent(width, height));
        _window_map_lock.unlock();
        requestXRenderPath(hh);
    }

    void GlfwManager::window_refresh_callback(GLFWwindow* window)
    {
        _window_map_lock.lock();
        auto& hh = getWindowEventHousehold(window);
        _window_map_lock.unlock();
        requestXRenderPath(hh);
    }

    void GlfwManager::window_framebuffer_size_callback(GLFWwindow* window,
                                                       int width, int height)
    {
        _window_map_lock.lock();
        auto& hh = getWindowEventHousehold(window);
        hh._events.push_back(new WindowResizeEvent(width, height));
        _window_map_lock.unlock();
        requestXRenderPath(hh);
    }

    void GlfwManager::error_callback(int id, const char* text)
    {
        // problem is this only kills this thread
        // TODO: create bool glErrorOccured function and check it in pgt
        // engine
        PGT_ASSERT(false, "GLFW Error: %i: %s", id, text);
    }
    // inspired by stackoverflow thread:
    // http://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
    void GlfwManager::get_current_monitor(GLFWwindow* window,
                                          GLFWmonitor** monitor, int* width,
                                          int* height, int* x, int* y)
    {
        int nmonitors, i;
        int wx, wy, ww, wh;
        int mx, my, mw, mh;
        int overlap, bestoverlap;
        GLFWmonitor* bestmonitor;
        GLFWmonitor** monitors;
        const GLFWvidmode* mode;

        bestoverlap = 0;
        bestmonitor = NULL;

        glfwGetWindowPos(window, &wx, &wy);
        glfwGetWindowSize(window, &ww, &wh);
        monitors = glfwGetMonitors(&nmonitors);

        for (i = 0; i < nmonitors; i++) {
            mode = glfwGetVideoMode(monitors[i]);
            glfwGetMonitorPos(monitors[i], &mx, &my);
            mw = mode->width;
            mh = mode->height;

            overlap = pgt::max(0, pgt::min(wx + ww, mx + mw) - pgt::max(wx, mx)) *
                      pgt::max(0, pgt::min(wy + wh, my + mh) - pgt::max(wy, my));

            if (bestoverlap < overlap) {
                bestoverlap = overlap;
                *monitor = monitors[i];
                *x = mx;
                *y = my;
                *width = mw;
                *height = mh;
            }
        }
    }
}
