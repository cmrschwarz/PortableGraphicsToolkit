#include "GlFontInternal.h"
#include <freetype_gl/freetype-gl.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    namespace plattform {

        GlFontInternal::GlFontInternal(const std::string& name, size_t size,
                                       IStreamReader& sr)
            : _name(name), _size(size), _managed(false)
        {
            int ias = getInitialAtlasSize(size);
            ftgl::texture_atlas_t* ta = ftgl::texture_atlas_new(ias, ias, 1);
            size_t filesize = sr.readToEnd(&_data);
            _texture_font = _texture_font =
                ftgl::texture_font_new_from_memory(ta, size, _data, filesize);
            // delete data;
            glGenTextures(1, &ta->id);
        }

        GlFontInternal::~GlFontInternal()
        {
            glDeleteTextures(1, &_texture_font->atlas->id);
            ftgl::texture_atlas_delete(_texture_font->atlas);
            ftgl::texture_font_delete(_texture_font);
            _data;
        }

        int GlFontInternal::getAscender() const
        {
            return _texture_font->ascender;
        }

        int GlFontInternal::getDescender() const
        {
            return -_texture_font->descender;
        }

        int GlFontInternal::getYOffsetMax() const
        {
            return getAscender() + getDescender();
        }

        int GlFontInternal::getBaselineOffset() const
        {
            return getAscender();
        }

        const std::string& GlFontInternal::getName() const
        {
            return _name;
        }

        size_t GlFontInternal::getSize() const
        {
            return _size;
        }

        GLuint GlFontInternal::getTid()
        {
            return _texture_font->atlas->id;
        }

        ftgl::texture_glyph_t* GlFontInternal::getGlyph(char c)
        {
            ftgl::texture_glyph_t* p =
                ftgl::texture_font_find_glyph(_texture_font, &c);
            if (p == nullptr) {
                ftgl::texture_font_load_glyph(_texture_font, &c);
                p = ftgl::texture_font_find_glyph(_texture_font, &c);
                while (p == nullptr) {
                    ftgl::texture_font_enlarge_atlas(
                        _texture_font, _texture_font->atlas->width * 2,
                        _texture_font->atlas->height * 2);
                    PGT_LOG_DEBUG("Increased Texture Atlas Size");
                    ftgl::texture_font_load_glyph(_texture_font, &c);
                    p = ftgl::texture_font_get_glyph(_texture_font, &c);
                }
                updateTexture();
            }
            return p;
        }

        bool GlFontInternal::isManaged()
        {
            return _managed;
        }

        void GlFontInternal::setManaged(bool value)
        {
            _managed = value;
        }

        pgt::vec3i GlFontInternal::measureString(const std::string& text)
        {
            if (text.size() == 0) return pgt::vec3i(0, 0, 0);
            const char* str = text.c_str();
            float width = 0;
            int y_low_max = 0;
            int offset_y_max = 0;
            char curr, prev;
            ftgl::texture_glyph_t* glyph = nullptr;
            for (int i = 0; i < text.size(); i++) {
                curr = str[i];
                glyph = getGlyph(curr);
                if (i > 0) {
                    width += ftgl::texture_glyph_get_kerning(glyph, &prev);
                }
                width += glyph->advance_x;
                if (glyph->offset_y > offset_y_max)
                    offset_y_max = glyph->offset_y;
                int y_low = glyph->height - glyph->offset_y;
                if (y_low > y_low_max) y_low_max = y_low;
                int prev = curr;
            }
            width -= glyph->advance_x - glyph->offset_x - glyph->width;
            int baseline = getAscender();
            // TODO: investigate why we need -1 here
            return vec3i((int)width, baseline + y_low_max - 1,
                         baseline - offset_y_max);
        }

        void GlFontInternal::updateTexture()
        {
            GLint interp = (_texture_font->size >= 30) ? GL_LINEAR : GL_LINEAR;
            glBindTexture(GL_TEXTURE_2D, _texture_font->atlas->id);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                            GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                            GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interp);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interp);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA,
                         _texture_font->atlas->width,
                         _texture_font->atlas->height, 0, GL_ALPHA,
                         GL_UNSIGNED_BYTE, _texture_font->atlas->data);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        int GlFontInternal::getInitialAtlasSize(int fontsize)
        {
            static const int sizes[] = {64, 128, 256, 512, 1024};
            // tweakable. allows for ~36 characters. should be enough in most
            // cases
            int target_size = fontsize * 2;
            for (int i = 0; i < 4; i++) {
                if (target_size < sizes[i]) return sizes[i];
            }
            return sizes[4];
        }
    }
}