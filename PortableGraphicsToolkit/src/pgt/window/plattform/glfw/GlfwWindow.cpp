#include "GlfwWindow.h"
#include <GLFW/glfw3.h>
#include "PGTEngine_Glfw.h"

namespace pgt {
    namespace plattform {
        //[TODO] some of this behaviour might be abstracted into game window one
        // day
        GlfwWindow::GlfwWindow(const window_creation_hints& ch)
        {
            _fullscreen = ch.fullscreen;
            _fs_requested_width = ch.fullscreen_width;
            _fs_requested_height = ch.fullscreen_height;
            _title = ch.title;
            _width = ch.width;
            _height = ch.height;
            _target_tps = ch.tps;
            _pos_x = DEFAULT;
            _pos_y = DEFAULT;
            if (ch.fullscreen == true) {
                _fs_width = _fs_requested_width;
                _fs_height = _fs_requested_height;
                _glfw_window = PGTEngine_Glfw::createWindow(
                    window_data(this, &_fs_width, &_fs_height, nullptr, nullptr,
                                _title.c_str(), _fullscreen, nullptr),
                    this);
            }
            else {
                _glfw_window = PGTEngine_Glfw::createWindow(
                    window_data(this, &_width, &_height, &_pos_x, &_pos_y,
                                _title.c_str(), _fullscreen, nullptr),
                    this);
            }
            _rendering_context.setWindow(this);
            PGTEngine_Glfw::setRenderingContext(_rendering_context);
            if (!_fullscreen) {
                _viewport = Rectangle(0, 0, _width, _height);
            }
            else {
                _viewport = Rectangle(0, 0, _fs_width, _fs_height);
            }
        }
        GlfwWindow::~GlfwWindow()
        {
        }

        IRenderingContext& GlfwWindow::getRenderingContext()
        {
            return _rendering_context;
        }

        GlfwGlRenderingContext& GlfwWindow::getSpecializedRenderingContext()
        {
            return _rendering_context;
        }

        bool GlfwWindow::isNiceResizeEnabled()
        {
            return !(_fps < 30);
        }

        int GlfwWindow::getFPS() const
        {
            return _fps;
        }

        int GlfwWindow::getTPS() const
        {
            return _tps;
        }

        int GlfwWindow::getTargetTPS() const
        {
            return _target_tps;
        }

        int GlfwWindow::getCurrentTick() const
        {
            return _tick_of_second;
        }

        float GlfwWindow::getTickPercentage() const
        {
#if 0
			float time_per_tick = 1000.0f / _target_tps;
			float percentage = (float)(_time_since_last_tick.getElapsedTimeMillis()) / time_per_tick;
			percentage = pgt::clamp(percentage, 0.0f, 1.0f);
			PGT_LOG_INFO("%f", percentage);
			return percentage;
#else
            // ITS MAGIC! DONT TOUCH
            //(Exponential Decay function for smooth movement interpolation
            // between
            // frames)
            float springiness = 42;  // can be tweaked
            float d =
                1.0f -
                std::exp(std::log(0.5f) * springiness *
                         (float)_time_since_last_tick.getElapsedTimeSeconds());
            return d;
#endif
        }

        int GlfwWindow::getCurrentFrame() const
        {
            return _frames_this_second;
        }

        void GlfwWindow::setVSync(bool vsync)
        {
            _vsync = vsync;
            glfwSwapInterval(_vsync ? 1 : 0);
        }

        bool GlfwWindow::isVSynced() const
        {
            return _vsync;
        }

        void GlfwWindow::setMouseGrab(bool mouse_grab)
        {
            _mouse_grab = mouse_grab;
            int mode = (mouse_grab) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
            // needs to be called on "main thread" according to specs
            GlfwManager::executeOnPollThread(
                [=] { glfwSetInputMode(_glfw_window, GLFW_CURSOR, mode); });
        }

        void GlfwWindow::setRequestedFullscreenResolution(int width, int height)
        {
            _fs_requested_width = width;
            _fs_requested_height = height;
            if (_fullscreen) setFullscreen(true);
        }

        void GlfwWindow::setFullscreen(bool fullscreen)
        {
            _fullscreen = fullscreen;
            // TODO: change this to be a function in manager
            if (_fullscreen) {
                GlfwManager::executeOnPollThread(
                    [&]() {
                        int w, h;
                        GLFWmonitor* monitor;
                        GlfwManager::get_current_monitor(
                            _glfw_window, &monitor, &w, &h, &_fs_x, &_fs_y);
                        if (_fs_requested_width == DEFAULT) _fs_width = w;
                        if (_fs_requested_height == DEFAULT) _fs_height = h;
                        glfwSetWindowMonitor(_glfw_window, monitor, 0, 0,
                                             _fs_width, _fs_height,
                                             GLFW_DONT_CARE);
                        glfwGetWindowSize(_glfw_window, &_fs_width,
                                          &_fs_height);
                    },
                    true);
            }
            else {
                if (_pos_x == DEFAULT && _pos_y == DEFAULT) {
                    _pos_x = 60;
                    _pos_y = 60;
                    // TODO: revisit
                }
                GlfwManager::executeOnPollThread(
                    [=]() {
                        glfwSetWindowMonitor(_glfw_window, nullptr, _pos_x,
                                             _pos_y, _width, _height,
                                             GLFW_DONT_CARE);
                    },
                    true);
            }
        }

        bool GlfwWindow::isFullscreen() const
        {
            return _fullscreen;
        }

        void GlfwWindow::setSize(int width, int height)
        {
            _width = width;
            _height = height;
            if (!_fullscreen) {
                GlfwManager::executeOnPollThread(
                    [=] { glfwSetWindowSize(_glfw_window, _width, _height); });
            }
        }

        int GlfwWindow::getWidth() const
        {
            if (_fullscreen) return _fs_width;
            return _width;
        }

        int GlfwWindow::getHeight() const
        {
            if (_fullscreen) return _fs_height;
            return _height;
        }

        void GlfwWindow::setTitle(std::string& title)
        {
            _title = title;
            GlfwManager::executeOnPollThread(
                [=] { glfwSetWindowTitle(_glfw_window, _title.c_str()); });
        }

        const std::string& GlfwWindow::getTitle() const
        {
            return _title;
        }

        void GlfwWindow::close()
        {
            auto w = _glfw_window;
            GlfwManager::executeOnPollThread([w]() { glfwDestroyWindow(w); });
            _should_close = true;
        }

        bool GlfwWindow::isClosed()
        {
            return _should_close;
        }

        const pgt::Rectangle& GlfwWindow::getViewport()
        {
            return _viewport;
        }

        void GlfwWindow::raise(Event& e)
        {
            if (e.ID == KeyEvent::ID) {
                setKeyDown(e.cast<KeyEvent>().key, e.cast<KeyEvent>().down);
            }
            else if (e.ID == MouseClickEvent::ID) {
                setKeyDown(e.cast<MouseClickEvent>().button,
                           e.cast<KeyEvent>().down);
            }
            else if (e.ID == MouseMoveEvent::ID) {
                auto& ec = e.cast<MouseMoveEvent>();
                setCursorPosition(ec.x, ec.y);
            }
            else if (e.ID == WindowResizeEvent::ID) {
                auto& ec = e.cast<WindowResizeEvent>();
                _viewport = Rectangle(0, 0, ec.width, ec.height);
                // TODO: make seperate framebuffer event
                if (!_fullscreen) {
                    _width = ec.width;
                    _height = ec.height;
                }

                // TODO: evaluate(multi window)
                glViewport(0, 0, ec.width, ec.height);
            }
            else if (e.ID == WindowCloseEvent::ID) {
                close();
            }
            else if (e.ID == WindowMoveEvent::ID) {
                if (!_fullscreen) {
                    _pos_x = e.cast<WindowMoveEvent>().pos_x;
                    _pos_y = e.cast<WindowMoveEvent>().pos_y;
                }
            }
            EventHandlerContainer<EventHandler, Scene>::raise(e);
        }
        void GlfwWindow::internal_update()
        {
            if (_should_close) return;

            // never falling behind more than one tick
            float time_per_tick = 1000.0f / _target_tps;
            int tc = 0;
            double elapsed;
            while (true) {
                elapsed = _update_timer.getElapsedTimeMillis();
                if (elapsed <= _tick_of_second * time_per_tick ||
                    (elapsed >= 1000 && _tick_of_second >= _target_tps))
                    break;
                internal_tick();
                tc++;
            }
            if (tc > 1) PGT_LOG_WARN("MULTITICK: %i", tc);
            //
            if (_update_timer.getElapsedTimeMillis() >= 1000) {
                _update_timer.setStart();
                _fps = _frames_this_second;
                _tps = _tick_of_second;
                _tick_of_second = 0;
                _frames_this_second = 0;
            }
            _frames_this_second++;

            glClear(GL_COLOR_BUFFER_BIT);
            raise(RenderEvent());
            // here
            glfwSwapBuffers(_glfw_window);
        }
        void GlfwWindow::internal_tick()
        {
            raise(TickEvent());
            _time_since_last_tick.setStart();
            _tick_of_second++;
            wipeKeyPresses();
        }

        void GlfwWindow::internal_makeContextCurrent()
        {
            glfwMakeContextCurrent(_glfw_window);
        }
    }
}