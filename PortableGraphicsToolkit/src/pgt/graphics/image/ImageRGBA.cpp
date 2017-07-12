#include "ImageRGBA.h"
#include <stdio.h>
#include <cstring>
#include <pgt/target_settings/target_settings.h>
namespace pgt {

    uint8_t* ImageRGBA::getData() const
    {
        return (uint8_t*)_data;
    }

    size_t ImageRGBA::getWidth() const
    {
        return _width;
    }

    size_t ImageRGBA::getHeight() const
    {
        return _height;
    }


    size_t ImageRGBA::getDataSize() const
    {
        return _width * _height * sizeof(*_data);
    }

    pgt::ImageFormat ImageRGBA::getFormat() const
    {
        return ImageFormat::RGBA_32;
    }

    ImageRGBA::ImageRGBA(size_t width, size_t height, bool zero_initialize)
        : _width(width), _height(height)
    {
        _data = new uint32_t[_width * _height];
        if (zero_initialize) {
            memset(_data, 0, _width * _height * sizeof(*_data));
        }
    }
    ImageRGBA::ImageRGBA(Image& img)
        : _width(img.getHeight()), _height(img.getHeight())
    {
        _data = new uint32_t[_width * _height];
        switch (img.getFormat()) {
        case ImageFormat::RGB_24:
            fromRGB24(img, false);
            break;
        case ImageFormat::BGR_24:
            fromRGB24(img, true);
            break;
        case ImageFormat::RGB_16_565:
            fromRGB565(img, false);
            break;
        case ImageFormat::BGR_16_565:
            fromRGB565(img, true);
            break;
        case ImageFormat::BGRA_32:
            fromBGRA32(img);
            break;
        case ImageFormat::RGBA_32:
            memcpy(_data, img.getData(), img.getDataSize());
            break;
        }
    }

    ImageRGBA::~ImageRGBA()
    {
        delete[] _data;
    }

    size_t ImageRGBA::getXStride() const
    {
        return sizeof(*_data);
    }

    size_t ImageRGBA::getYStride() const
    {
        return _width * getXStride();
    }

    uint32_t ImageRGBA::turnColorToImagePixel(Color c) const
    {
        return c.toNetworkOrder();
    }

    void ImageRGBA::setPixelAt(uint8_t* pos, uint32_t pix_val)
    {
        uint32_t* dpos = (uint32_t*)pos;
        *dpos = pix_val;
    }

    void ImageRGBA::setPixelAt(const vec2i& pos, Color c)
    {
        *((uint32_t*)(getData() + pos.x * getXStride() +
                      pos.y * getYStride())) = c.toNetworkOrder();
    }

    void ImageRGBA::fromRGB24(Image& img, bool bgr)
    {
        uint8_t* dest = (uint8_t*)_data;
        const uint8_t* src = img.getData();
        const uint8_t* end_src = src + img.getDataSize();
        while (src < end_src) {
            dest[3] = 0xFF;
            if (bgr) {
                dest[0] = src[2];
                dest[1] = src[1];
                dest[2] = src[0];
            }
            else {
                dest[0] = src[0];
                dest[1] = src[1];
                dest[2] = src[2];
            }
            src += 3;
            dest += 4;
        }
    }
    void ImageRGBA::fromRGB565(Image& img, bool bgr)
    {
        uint8_t* dest = (uint8_t*)_data;
        const uint16_t* src = (const uint16_t*)img.getData();
        const uint16_t* end_src = src + img.getDataSize();
        while (src < end_src) {
            dest[3] = 0xFF;
            if (bgr) {
                dest[2] = (*src & 0xF800) >> (5 + 6);
                dest[1] = (*src & 0x07E0) >> (5);
                dest[0] = (*src & 0x001F);
            }
            else {
                dest[0] = (*src & 0xF800) >> (5 + 6);
                dest[1] = (*src & 0x07E0) >> (5);
                dest[2] = (*src & 0x001F);
            }
            src++;
            dest += 4;
        }
    }

    void ImageRGBA::fromBGRA32(Image& img)
    {
        uint8_t* dest = (uint8_t*)_data;
        const uint8_t* src = img.getData();
        const uint8_t* end_src = src + img.getDataSize();
        while (src < end_src) {
            dest[0] = src[2];
            dest[1] = src[1];
            dest[2] = src[0];
            dest[3] = src[3];
            src += 4;
            dest += 4;
        }
    }
}