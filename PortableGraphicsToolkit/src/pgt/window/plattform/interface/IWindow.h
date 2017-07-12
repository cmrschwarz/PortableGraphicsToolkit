#pragma once
#include <string>
namespace pgt {
    // TODO: seperate this into game_window_creation_hints etc.
    struct window_creation_hints {
    public:
        static const int DEFAULT = -1;

    public:
        bool resizable = true;
        bool fullscreen = false;
        int width = 640;
        int height = 480;
        // if both these are DEFAULT it uses default screen resolution
        // otherwise you'll get the closest possible viewmode to the
        // values you specified
        int fullscreen_width = DEFAULT;
        int fullscreen_height = DEFAULT;
        int tps = 30;
        const char* title = "PGTEngine";
        bool undecorated = false;
        bool vSync = true;
    };
    class IRenderingContext;
    class IWindow {
    public:
        virtual ~IWindow(){};

    public:
        enum class NiceResizeRule : int {
            disabled = -1,
            enabled = 0,
            enabled_over_30_fps = 30,
            enabled_over_40_fps = 40,
            enabled_over_50_fps = 50,
            enabled_over_60_fps = 60,
        };
        virtual IRenderingContext& getRenderingContext() = 0;
        virtual bool isNiceResizeActive() = 0;
        virtual void setNiceResizeRule(NiceResizeRule r) = 0;

        virtual void setVSync(bool vsync) = 0;
        virtual bool isVSynced() const = 0;

        virtual void setMouseGrab(bool mouse_grab) = 0;
        virtual bool isMouseGrabed() const = 0;
        virtual void setRequestedFullscreenResolution(int width,
                                                      int height) = 0;
        virtual void setFullscreen(bool fullscreen) = 0;
        virtual bool isFullscreen() const = 0;
        // only affects windowed mode
        virtual void setSize(int width, int height) = 0;
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual void setTitle(const std::string& title) = 0;
        virtual const std::string& getTitle() const = 0;
        virtual void close() = 0;
        virtual bool shouldClose() const = 0;
        virtual bool prefersEventBased() const = 0;
        virtual void clear() = 0;
        virtual void swapBuffers() = 0;

    protected:
        virtual void internal_update() = 0;
    };
}