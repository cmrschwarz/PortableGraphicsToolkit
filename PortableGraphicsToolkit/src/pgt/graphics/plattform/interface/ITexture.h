#pragma once
#include <pgt/graphics/Image/IImage.h>  //for convenience
namespace pgt {
    class ITexture {
      protected:
        ~ITexture(){};

      public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual void setImage(const IImage& img) = 0;
        virtual ImageFormat getFormat() const = 0;
        virtual void copyData(void* buffer) const = 0;
    };
}