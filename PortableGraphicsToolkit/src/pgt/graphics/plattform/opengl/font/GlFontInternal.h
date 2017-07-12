#pragma once
#include <pgt/utils/primitives.h>
#include <pgt/io/istreams/IStreamReader.h>
#include <string>
#include <pgt/maths/maths.h>
namespace ftgl {
    struct texture_font_t;
    struct texture_atlas_t;
    struct texture_glyph_t;
}
namespace pgt {
    namespace plattform {
        struct VertexData;

        class GlFontInternal {
        private:
            bool _managed;
            std::string _name;
            size_t _size;
            ftgl::texture_font_t* _texture_font;
            void* _data;

        public:
            // TODO: create default folder and stuff
            GlFontInternal(const std::string& name, size_t size,
                           IStreamReader& sr);
            //rvalue trick
            GlFontInternal(const std::string& name, size_t size,
                           IStreamReader&& sr):GlFontInternal(name,size,sr){}
            ~GlFontInternal();


        public:
            int getAscender() const;
            int getDescender() const;
            int getYOffsetMax() const;
            int getBaselineOffset() const;
            const std::string& getName() const;
            size_t getSize() const;
            GLuint getTid();
            ftgl::texture_glyph_t* getGlyph(char c);
            bool isManaged();
            void setManaged(bool value);
            vec3i measureString(const std::string& text);

        private:
            void updateTexture();
            static int getInitialAtlasSize(int fontsize);
        };
    }
}