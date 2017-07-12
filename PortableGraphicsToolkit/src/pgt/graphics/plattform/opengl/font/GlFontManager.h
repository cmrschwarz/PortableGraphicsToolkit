#pragma once
#include <vector>
#include <pgt/graphics/plattform/opengl/font/GlFont.h>
#include <pgt/graphics/plattform/interface/IFontManager.h>
#include <pgt/graphics/graphics_2d.h>
namespace pgt {
    namespace plattform {
        // TODO: maybe do one font manager per app and not per rendering context
        class GlFontManager : public IFontManager {
        private:
            std::vector<GlFontInternal*> _fonts;

            GlFontInternal _default_font_internal;
            GlFont _default_font;

        public:
            GlFontManager();
            ~GlFontManager();


        public:
            GlFontInternal* getFont(const std::string& name, size_t size);
            void submitFont(const IFont& font);

        public:
            Font& getDefaultFont() override;
        };
    }
}
