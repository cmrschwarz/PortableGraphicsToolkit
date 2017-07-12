#include "SdlGlRenderingContext.h"
#include <pgt/window/plattform/sdl/SdlWindow.h>
namespace pgt {
    namespace plattform {
        SdlGlRenderingContext::SdlGlRenderingContext(SdlWindow& w)
            : GlRenderingContext(w)
        {
        }

        pgt::Window& SdlGlRenderingContext::getWindow() const
        {
            return *_window;
        }

        void SdlGlRenderingContext::setWindow(SdlWindow* win)
        {
            _window = win;
        }

        void SdlGlRenderingContext::setContextCurrent()
        {
            _window->internal_makeContextCurrent();
        }

        GlFontManager& SdlGlRenderingContext::getFontManager()
        {
            return _font_manager;
        }
    }
}
