#include "GlTexture.h"
#include <GL/glew.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    namespace plattform {
        GlTexture::GlTexture(size_t width, size_t height)
            : _width(width), _height(height)
        {
            setupTexture();
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, NULL);
        }
        GlTexture::GlTexture(const IImage& img)
        {
            setupTexture();
            GlTexture::setImage(img);
        }
        // TODO: refactor this
        GlTexture::GlTexture(size_t width, size_t height, bool grayscale)
            : _width(width), _height(height)
        {
            setupTexture();


            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height,
                         0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

            glBindTexture(GL_TEXTURE_2D, 0);
            GLenum status = glGetError();
            PGT_DEBUG_ASSERT(status == GL_NO_ERROR, "GL Error %i", status)
        }

        GlTexture::~GlTexture()
        {
            glDeleteTextures(1, &_tid);
        }

        int GlTexture::getWidth() const
        {
            return _width;
        }

        int GlTexture::getHeight() const
        {
            return _height;
        }

        void GlTexture::setImage(const IImage& img)
        {
            _width = img.getWidth();
            _height = img.getHeight();
            glBindTexture(GL_TEXTURE_2D, getTID());
            auto format = getGlFormat(img.getFormat());
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, format,
                         GL_UNSIGNED_BYTE, img.getData());
        }

        ImageFormat GlTexture::getFormat() const
        {
            // TODO: allow transparency and all
            return ImageFormat::RGBA_32;
        }

        void GlTexture::copyData(void* buffer) const
        {
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            glBindTexture(GL_TEXTURE_2D, getTID());

            size_t buffer_size = _width * _height * 3;
            glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, buffer);
            // restore default
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            glPixelStorei(GL_PACK_ALIGNMENT, 4);
        }

        GLuint GlTexture::getTID() const
        {
            return _tid;
        }

        void GlTexture::setupTexture()
        {
            glGenTextures(1, &_tid);
            glBindTexture(GL_TEXTURE_2D, _tid);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        size_t GlTexture::getGlFormat(ImageFormat imgf)
        {
            switch (imgf) {
            case ImageFormat::RGBA_32:
                return GL_RGBA;
            case ImageFormat::BGRA_32:
                return GL_BGRA;
            case ImageFormat::RGB_24:
                return GL_RGB;
            case ImageFormat::BGR_24:
                return GL_BGR;
            case ImageFormat::RGB_16_565:
                return GL_RGB565;
            case ImageFormat::RGB_16_555:
                return GL_RGB5;
            default:
                PGT_ASSERT(false, "Unsopperted Format");
            }
        }
    }
}