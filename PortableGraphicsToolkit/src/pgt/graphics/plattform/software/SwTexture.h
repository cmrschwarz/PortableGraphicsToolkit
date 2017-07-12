#pragma once
#include <pgt/graphics/plattform/interface/ITexture.h>
#include <pgt/graphics/image/IImage.h>
namespace pgt {
    class SwTexture : public ITexture {
      public:
        SwTexture(size_t width, size_t height);
        SwTexture(const IImage& img);
        ~SwTexture();

      public:
        void copyData(void* buffer) const override;
        void setImage(const IImage& img) override;
        ImageFormat getFormat() const override;
        int getHeight() const override;
        int getWidth() const override;
    };
}