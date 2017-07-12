#pragma once
#include <pgt/utils/primitives.h>
namespace pgt {
    namespace plattform {
        class GlIndexBuffer {
          public:
            GlIndexBuffer();
            ~GlIndexBuffer();

          private:
            GLuint _ibo;

          public:
            void initForRectangles(int min_index_count);
            GLuint getID();
            int getIndexCount();
        };
    }
}