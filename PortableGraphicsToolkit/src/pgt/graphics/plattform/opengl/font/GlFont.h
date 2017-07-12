#pragma once
#include <string.h>
#include <pgt/graphics/plattform/interface/IFont.h>
#include <pgt/maths/maths.h>
#include <pgt/io/istreams/istreams.h>
namespace pgt {
    namespace plattform {
        class GlFontInternal;
        class GlFont : public IFont {
            friend class GlFontManager;
            mutable GlFontInternal* _font_internal;  // for measure string

        public:
            // careful: this constructor doesn't put the font inside the manager
            // use FontManager.submitFont(f) for that
            GlFont(const std::string& name, size_t size, IStreamReader&& sr):GlFont(name,size,sr){}
            GlFont(const std::string& name, size_t size, IStreamReader& sr);
            GlFont(const std::string& name, size_t size);
            GlFont(GlFontInternal& f);
            ~GlFont();

        public:
            const std::string& getName() const;
            size_t getSize() const;
            int getAscender() const;
            int getDescender() const;
            int getBaselineOffset() const;
            int getYOffsetMax() const;
            int getYOffsetMin() const;
            // TODO: evaluate this being non const
            pgt::vec3i measureString(const std::string& text) const override;

        public:
            // TODO: maybe make this private
            GlFontInternal& getInternalFont();
        };
    }
}