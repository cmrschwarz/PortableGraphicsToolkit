#pragma once
#include <pgt/graphics/plattform/interface/IRenderingContext.h>
#include <pgt/graphics/plattform/opengl/GlFontManager.h>

namespace pgt {
    namespace plattform {
        class GlfwWindow;
        class GlfwGlRenderingContext : public IRenderingContext {
            GlfwWindow* _window;
            GlFontManager _font_manager;

          public:
            GlfwGlRenderingContext();
            void setWindow(GlfwWindow* win);
            void setContextCurrent() override;
            GlFontManager& getFontManager();
        };
    }
}