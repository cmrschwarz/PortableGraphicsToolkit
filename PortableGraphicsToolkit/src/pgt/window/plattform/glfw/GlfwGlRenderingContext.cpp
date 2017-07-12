#include "GlfwGlRenderingContext.h"
#include "GlfwWindow.h"
#include <SDL2/SDL.h>
namespace pgt {
    namespace plattform {
        GlfwGlRenderingContext::GlfwGlRenderingContext()
        {
        }

        void GlfwGlRenderingContext::setWindow(GlfwWindow* win)
        {
            _window = win;
        }

        void GlfwGlRenderingContext::setContextCurrent()
        {
            _window->internal_makeContextCurrent();
        }

        GlFontManager& GlfwGlRenderingContext::getFontManager()
        {
            return _font_manager;
        }
    }
}
