#include "GlFont.h"
#include <pgt/window/engine.h>
#include <pgt/window/plattform/interface/IAPP.h>
#include <pgt/graphics/plattform/interface/IRenderingContext.h>
#include <pgt/io/logger/logger.h>
#include "GlFontInternal.h"
namespace pgt {
    namespace plattform {

        GlFont::GlFont(const std::string& name, size_t size, IStreamReader& sr)
        {
            _font_internal = new GlFontInternal(name, size, sr);
        }

        GlFont::GlFont(const std::string& name, size_t size)
        {
            _font_internal =
                ((GlFontManager&)engine::getRenderingContextCurrent()
                     .getFontManager())
                    .getFont(name, size);
            PGT_ASSERT(_font_internal, "Font doesnt exist");
        }

        GlFont::GlFont(GlFontInternal& f)
        {
            _font_internal = &f;
        }

        GlFont::~GlFont()
        {
            if (_font_internal->isManaged() == false) delete _font_internal;
        }

        GlFontInternal& GlFont::getInternalFont()
        {
            return *_font_internal;
        }

        const std::string& GlFont::getName() const
        {
            return _font_internal->getName();
        }

        size_t GlFont::getSize() const
        {
            return _font_internal->getSize();
        }

        int GlFont::getAscender() const
        {
            return _font_internal->getAscender();
        }

        int GlFont::getDescender() const
        {
            return _font_internal->getDescender();
        }

        int GlFont::getBaselineOffset() const
        {
            return _font_internal->getBaselineOffset();
        }

        int GlFont::getYOffsetMax() const
        {
            return _font_internal->getYOffsetMax();
        }

        pgt::vec3i GlFont::measureString(const std::string& text) const
        {
            return _font_internal->measureString(text);
        }
    }
}
