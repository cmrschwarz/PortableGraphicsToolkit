#pragma once
#include <pgt/graphics/plattform/interface/ITexture.h>
#include <pgt/utils\primitives.h>
#include <pgt/graphics/image/IImage.h>

namespace pgt {
    namespace plattform {
        class GlTexture : public ITexture {
          private:
            GLuint _tid;
            size_t _width;
            size_t _height;

          public:
            GlTexture(size_t width, size_t height);
            GlTexture(size_t width, size_t height, bool grayscale);
            GlTexture(const IImage& img);
            ~GlTexture();

          public:
            int getWidth() const override;
            int getHeight() const override;
            void setImage(const IImage& img) override;
            ImageFormat getFormat() const override;
            void copyData(void* buffer) const override;

          public:
            GLuint getTID() const;

          private:
            static size_t getGlFormat(ImageFormat imgf);
            void setupTexture();
        };
    }
}