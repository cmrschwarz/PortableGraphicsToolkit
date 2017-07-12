#pragma once
#include <pgt/utils/Stopwatch.h>
#include <pgt/window/gui/Rectangle.h>
#include <pgt/window/layers/LayerContainer.h>
#include <pgt/window/layers/RenderingLayer.h>
#include <pgt/window/gui/GuiComponentContainer.h>
#include <pgt/window/gui/events/events.h>
#include <pgt/window/plattform/sdl/SdlGlRenderingContext.h>
#include <pgt/window/plattform/interface/IWindow.h>
struct SDL_Window;
typedef void* SDL_GLContext;
namespace pgt {
    namespace plattform {
        class SdlWindow : public IWindow,
                          public LayerContainer<RenderingLayer, RenderingLayer>,
                          public InputManager {
            friend class SdlApp;
            friend class SdlGlRenderingContext;

        private:
        public:
            static const int DEFAULT = -1;


        public:
            SdlWindow(const window_creation_hints& wch);
            ~SdlWindow() override;

        private:
            bool _dirty_state = false;
            bool _fullscreen;
            int _width, _height, _fs_width, _fs_height, _fs_requested_width,
                _fs_requested_height, _pos_x, _pos_y, _fs_x, _fs_y;
            SdlGlRenderingContext _rendering_context;
            std::string _title;
            bool _mouse_grab, _vsync;

            bool _should_close = false;
            SDL_Window* _sdl_window;
            SDL_GLContext _gl_context;

            Rectangle _viewport;

        public:
            IRenderingContext& getRenderingContext() override;
            bool isNiceResizeActive() override;
            void setNiceResizeRule(NiceResizeRule r) override;

        public:
            void setVSync(bool vsync) final override;
            bool isVSynced() const final override;
            void setMouseGrab(bool mouse_grab) override;
            bool isMouseGrabed() const override;
            void setRequestedFullscreenResolution(int width,
                                                  int height) override;
            void setMinimumSize(vec2i size);
            void setFullscreen(bool fullscreen) override;
            bool isFullscreen() const override;
            // only affects windowed mode
            void setSize(int width, int height) override;
            int getWidth() const final override;
            int getHeight() const final override;
            void setTitle(const std::string& title) override;
            const std::string& getTitle() const override;
            void close() override;
            bool shouldClose() const override;
            bool prefersEventBased() const override;

        public:
            // ATTENTION. This changes the active framebuffer to the windows one
            void clear() final override;
            // ATTENTION. This changes the active framebuffer to the windows one
            void swapBuffers() final override;

        public:
            void addLayer(RenderingLayer& l);
            void removeLayer(RenderingLayer& l);
            const Rectangle& getViewport();

            void raiseOnKeyDown(KeyDownEvent& e) override;
            void raiseOnMouseButtonDown(MouseButtonDownEvent& e) override;
            void raiseOnKeyUp(KeyUpEvent& e) override;
            void raiseOnMouseButtonUp(MouseButtonUpEvent& e) override;
            void raiseOnMouseMoved(MouseMoveEvent& e) override;
            void raiseOnResize(ResizeEvent& e) override;
            void raiseOnFocusGained() override;
            void raiseOnFocusLost() override;
            void raiseOnMove(MoveEvent& e) override;
            void raiseOnRender() override;

            virtual void onClosing(){};
            virtual void raiseOnClosing();

        protected:
            virtual void internal_update();

        private:
            void internal_makeContextCurrent();
            void internal_destroy();

        private:
            void tick();
        };
    }
}
