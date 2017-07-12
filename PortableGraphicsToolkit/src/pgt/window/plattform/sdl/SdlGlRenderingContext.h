#pragma once
#include <pgt/graphics/plattform/opengl/GLRenderingContext.h>
#include <pgt/graphics/plattform/opengl/font/GlFontManager.h>

namespace pgt {
    namespace plattform {
        class SdlWindow;
        class SdlGlRenderingContext : public GlRenderingContext {
            SdlWindow* _window;
            GlFontManager _font_manager;

          public:
            SdlGlRenderingContext(SdlWindow& w);
            Window& getWindow() const override;
            void setWindow(SdlWindow* win);
            void setContextCurrent() override;
            GlFontManager& getFontManager() override;
        };
    }
}
