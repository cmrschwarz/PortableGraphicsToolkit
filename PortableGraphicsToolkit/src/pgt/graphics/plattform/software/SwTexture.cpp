#include "SwTexture.h"
namespace pgt {
    int SwTexture::getWidth() const
    {
        return 0;
    }


    int SwTexture::getHeight() const
    {
        return 0;
    }


    ImageFormat SwTexture::getFormat() const
    {
        return ImageFormat::RGBA_32;
    }


    void SwTexture::copyData(void* buffer) const
    {
    }

    void SwTexture::setImage(const IImage& img)
    {
    }
}