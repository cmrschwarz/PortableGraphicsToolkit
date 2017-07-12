#include "SdlWindow.h"
#include "SdlApp.h"
#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <pgt/window/window.h>
#include <pgt/utils/debug/MessageBoxes.h>
namespace pgt {
    namespace plattform {

        // TODO: some of this behaviour might be abstracted into game window one
        // day
        SdlWindow::SdlWindow(const window_creation_hints& ch)
            : _rendering_context(*this)
        {
            _fullscreen = ch.fullscreen;
            _fs_requested_width = ch.fullscreen_width;
            _fs_requested_height = ch.fullscreen_height;
            _title = ch.title;
            _width = ch.width;
            _height = ch.height;

            _pos_x = DEFAULT;
            _pos_y = DEFAULT;
            SdlApp& app = (SdlApp&)(engine::getApp());
            if (_fullscreen == true) {
                _fs_width = _fs_requested_width;
                _fs_height = _fs_requested_height;
                sdl_window_data dat(*this, &_sdl_window, &_gl_context, true,
                                    _fs_width, _fs_height, _pos_x, _pos_y,
                                    _title.c_str(), _fullscreen, nullptr);
                app.createWindow(this, dat);
            }
            else {
                sdl_window_data dat(*this, &_sdl_window, &_gl_context, true,
                                    _width, _height, _pos_x, _pos_y,
                                    _title.c_str(), _fullscreen, nullptr);
                app.createWindow(this, dat);
            }
            _rendering_context.setWindow(this);

            app.setRenderingContext(_rendering_context);
            if (!_fullscreen) {
                _viewport = Rectangle(0, 0, _width, _height);
            }
            else {
                _viewport = Rectangle(0, 0, _fs_width, _fs_height);
            }
            setVSync(ch.vSync);
        }

        SdlWindow::~SdlWindow()
        {
            if (!shouldClose()) close();
            PGT_LOG_DEBUG("Window %s Destructed", getTitle().c_str());
        }

        IRenderingContext& SdlWindow::getRenderingContext()
        {
            return _rendering_context;
        }

        bool SdlWindow::isNiceResizeActive()
        {
            return true;
        }
        void SdlWindow::setNiceResizeRule(NiceResizeRule r)
        {
            return;  // TODO: implement
        }


        void SdlWindow::setVSync(bool vsync)
        {
            _vsync = vsync;
            SDL_GL_SetSwapInterval(_vsync ? 1 : 0);
        }

        bool SdlWindow::isVSynced() const
        {
            return _vsync;
        }
        bool SdlWindow::isMouseGrabed() const
        {
            return _mouse_grab;
        }
        void SdlWindow::setMouseGrab(bool mouse_grab)
        {
            _mouse_grab = mouse_grab;
            SDL_SetWindowGrab(_sdl_window,
                              (_mouse_grab) ? SDL_TRUE : SDL_FALSE);
            SDL_SetRelativeMouseMode((_mouse_grab) ? SDL_TRUE : SDL_FALSE);
        }

        void SdlWindow::setRequestedFullscreenResolution(int width, int height)
        {
            _fs_requested_width = width;
            _fs_requested_height = height;
            if (_fullscreen) setFullscreen(true);
        }

        void SdlWindow::setMinimumSize(vec2i size)
        {
            SDL_SetWindowMinimumSize(_sdl_window, size.x, size.y);
        }

        void SdlWindow::setFullscreen(bool fullscreen)
        {
            _fullscreen = fullscreen;
            // TODO: change this to bo real fullscreen
            if (_fullscreen == true) {
                _dirty_state = true;
                SDL_SetWindowFullscreen(_sdl_window,
                                        SDL_WINDOW_FULLSCREEN_DESKTOP);

                SDL_GetWindowSize(_sdl_window, &_fs_width, &_fs_height);
                _dirty_state = false;
            }
            else {
                if (_pos_x == DEFAULT && _pos_y == DEFAULT) {
                    _pos_x = 60;
                    _pos_y = 60;
                    // TODO: revisit
                }
                _dirty_state = true;
                SDL_SetWindowFullscreen(_sdl_window, 0);
                _dirty_state = false;
            }
        }

        bool SdlWindow::isFullscreen() const
        {
            return _fullscreen;
        }

        void SdlWindow::setSize(int width, int height)
        {
            _width = width;
            _height = height;
            SDL_SetWindowSize(_sdl_window, width, height);
        }

        int SdlWindow::getWidth() const
        {
            if (_fullscreen) return _fs_width;
            return _width;
        }

        int SdlWindow::getHeight() const
        {
            if (_fullscreen) return _fs_height;
            return _height;
        }

        void SdlWindow::setTitle(const std::string& title)
        {
            _title = title;
            SDL_SetWindowTitle(_sdl_window, title.c_str());
        }

        const std::string& SdlWindow::getTitle() const
        {
            return _title;
        }

        void SdlWindow::close()
        {
            _should_close = true;
        }

        bool SdlWindow::shouldClose() const
        {
            return _should_close;
        }

        bool SdlWindow::prefersEventBased() const
        {
            return false;
        }

        void SdlWindow::clear()
        {
            PGT_DEBUG_ASSERT(engine::getApp()
                                .getRenderingContext()
                                .isDefaultFramebufferEnabled(),
                            "Dont call Window.clear() while you have a "
                            "framebuffer enabled");
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void SdlWindow::swapBuffers()
        {
            PGT_DEBUG_ASSERT(engine::getApp()
                                .getRenderingContext()
                                .isDefaultFramebufferEnabled(),
                            "Dont call Window.swapBuffers() while you have a "
                            "framebuffer enabled");
            SDL_GL_SwapWindow(_sdl_window);
        }

        void SdlWindow::addLayer(RenderingLayer& l)
        {
            addComponent(l);
        }

        void SdlWindow::removeLayer(RenderingLayer& l)
        {
            removeComponent(l);
        }

        const pgt::Rectangle& SdlWindow::getViewport()
        {
            return _viewport;
        }

        void SdlWindow::raiseOnKeyDown(KeyDownEvent& e)
        {
            setKeyDown(e.key, true);
            Container_t::raiseOnKeyDown(e);
        }

        void SdlWindow::raiseOnMouseButtonDown(MouseButtonDownEvent& e)
        {
            setKeyDown(e.button, true);
            Container_t::raiseOnMouseButtonDown(e);
        }
        void SdlWindow::raiseOnKeyUp(KeyUpEvent& e)
        {
            setKeyDown(e.key, false);
            Container_t::raiseOnKeyUp(e);
        }

        void SdlWindow::raiseOnMouseButtonUp(MouseButtonUpEvent& e)
        {
            setKeyDown(e.button, false);
            Container_t::raiseOnMouseButtonUp(e);
        }
        void SdlWindow::raiseOnMouseMoved(MouseMoveEvent& e)
        {
            setCursorPositionOverride(e.x, e.y, e.x_rel, e.y_rel);
            Container_t::raiseOnMouseMoved(e);
        }

        void SdlWindow::raiseOnResize(ResizeEvent& e)
        {
            _viewport = Rectangle(0, 0, e.size_new.x, e.size_new.y);
            // TODO: make seperate framebuffer event
            if (_fullscreen) {
                _fs_width = e.size_new.x;
                _fs_height = e.size_new.y;
            }
            else {
                _width = e.size_new.x;
                _height = e.size_new.y;
            }
            // TODO: evaluate(multi window)
            glViewport(0, 0, e.size_new.x, e.size_new.y);
            Container_t::raiseOnResize(e);
        }

        void SdlWindow::raiseOnFocusGained()
        {
            if (_mouse_grab) setMouseGrab(true);
            Container_t::raiseOnFocusGained();
        }

        void SdlWindow::raiseOnFocusLost()
        {
            // disable mouse grab while not focused, but keep flag raiseO so we
            // can reset it
            if (_mouse_grab) {
                setMouseGrab(false);
                _mouse_grab = true;
            }
            Container_t::raiseOnFocusLost();
        }

        void SdlWindow::raiseOnMove(MoveEvent& e)
        {
            if (!_fullscreen) {
                _pos_x = e.pos_x;
                _pos_y = e.pos_y;
            }
            Container_t::raiseOnMove(e);
        }


        void SdlWindow::raiseOnRender()
        {
            RenderingLayer::raiseOnRender();
            forwardEvent(&ContainerComponent_t::raiseOnRender);
        }

        void SdlWindow::raiseOnClosing()
        {
            onClosing();
            callCallback(WindowCloseEvent());
            close();
        }

        void SdlWindow::internal_update()
        {
			
            clear();
			raiseOnRender();
            swapBuffers();
        }

        void SdlWindow::internal_makeContextCurrent()
        {
            SDL_GL_MakeCurrent(_sdl_window, _gl_context);
        }

        void SdlWindow::internal_destroy()
        {
            SDL_GL_DeleteContext(_gl_context);
            SDL_DestroyWindow(_sdl_window);
            engine::getApp().requestEventBased(true);
        }
    }
}
