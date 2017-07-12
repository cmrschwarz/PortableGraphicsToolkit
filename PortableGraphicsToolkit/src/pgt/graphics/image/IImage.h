#pragma once
#include <stdint.h>
#include <pgt/graphics/Color.h>
namespace pgt {

    // Represents byte order (from low to high memory address)
    enum class ImageFormat {
        RGBA_32,
        RGB_24,
        RGB_16_565,
        RGB_16_555,

        BGRA_32,
        BGR_24,
        BGR_16_565,
        BGR_16_555,

        GRAYSCALE_8,
        UNKNOWN,
    };
    class IImage {
      public:
        // gives you bottom left pixel
        virtual uint8_t* getData() const = 0;
        virtual size_t getWidth() const = 0;
        virtual size_t getHeight() const = 0;
        virtual size_t getDataSize() const = 0;
        virtual ImageFormat getFormat() const = 0;

      public:
        virtual size_t getXStride() const = 0;
        virtual size_t getYStride() const = 0;
        virtual uint32_t turnColorToImagePixel(Color c) const = 0;
        virtual void setPixelAt(uint8_t* data_pos, uint32_t pixel_val) = 0;
        virtual void setPixelAt(const vec2i& pos, Color c) = 0;
    };
}