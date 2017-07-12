#pragma once
#include <pgt/utils/Stopwatch.h>
#include <pgt/graphics/window/plattform/interface/IWindow.h>
#include <pgt/graphics/window/gui/Coordinates.h>
#include <pgt/graphics/window/layers/Scene.h>
#include <pgt/graphics/window/events/events.h>
#include <pgt/graphics/window/plattform/glfw/GlfwGlRenderingContext.h>
struct GLFWwindow;
namespace pgt {
    namespace plattform {
        class GlfwGlRenderingContext;
        class GlfwWindow : public EventHandlerContainer<EventHandler, Scene>,
                           public InputManager {
            friend class PGTEngine_Glfw;
            friend class GlfwGlRenderingContext;

          public:
            static const int DEFAULT = -1;


          public:
            GlfwWindow(const window_creation_hints& wch);
            ~GlfwWindow();

          private:
            bool _fullscreen;
            int _width, _height, _fs_width, _fs_height, _fs_requested_width,
                _fs_requested_height, _pos_x, _pos_y, _fs_x, _fs_y;
            GlfwGlRenderingContext _rendering_context;
            std::string _title;
            bool _mouse_grab, _vsync;
            int _target_tps;
            int _tick_of_second, _frames_this_second;
            int _fps, _tps;
            bool _should_close = false;
            GLFWwindow* _glfw_window;
            Stopwatch _update_timer;
            mutable Stopwatch _time_since_last_tick;  // in order to setEnd()
            Rectangle _viewport;

          public:
            IRenderingContext& getRenderingContext();
            GlfwGlRenderingContext& getSpecializedRenderingContext();
            bool isNiceResizeEnabled();
            int getFPS() const;
            int getTPS() const;
            int getTargetTPS() const;
            int getCurrentTick() const;
            float getTickPercentage() const;
            int getCurrentFrame() const;

          public:
            void setVSync(bool vsync);
            bool isVSynced() const;
            void setMouseGrab(bool mouse_grab);
            bool isMouseGrabed() const;
            void setRequestedFullscreenResolution(int width, int height);
            void setFullscreen(bool fullscreen);
            bool isFullscreen() const;
            // only affects windowed mode
            void setSize(int width, int height);
            int getWidth() const;
            int getHeight() const;
            void setTitle(std::string& title);
            const std::string& getTitle() const;
            void close();
            bool isClosed();

          public:
            const Rectangle& getViewport();
            void raise(Event& e) override;

          public:
          private:
            void internal_tick();
            void internal_makeContextCurrent();
            void internal_update();
        };
    }
}