#include "GlIndexBuffer.h"
#include <GL/glew.h>
namespace pgt {
    namespace plattform {
        GlIndexBuffer::GlIndexBuffer()
        {
            _ibo = -1;
        }

        GlIndexBuffer::~GlIndexBuffer()
        {
            glDeleteBuffers(1, &_ibo);
        }

        void GlIndexBuffer::initForRectangles(int min_index_count)
        {
            int index_count = min_index_count;
            int over = min_index_count % 6;
            if (over != 0) index_count += 6 - over;
            GLuint* indices = new GLuint[index_count];
            unsigned int offset = 0;
            for (int i = 0; i < index_count; i += 6) {
                indices[i + 0] = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                indices[i + 3] = offset + 2;
                indices[i + 4] = offset + 3;
                indices[i + 5] = offset + 0;

                offset += 4;
            }
            glGenBuffers(1, &_ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         index_count * sizeof(unsigned int), indices,
                         GL_STATIC_DRAW);
            delete[] indices;
        }

        GLuint GlIndexBuffer::getID()
        {
            return _ibo;
        }
    }
}