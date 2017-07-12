#pragma once
#include <cstdint>
#include <pgt/io/istreams/IStreamReader.h>
#include "Image.h"
namespace pgt {
    class ImageRGBA : public IImage {
    private:
        uint32_t* _data;
        size_t _width;
        size_t _height;


    public:
        ImageRGBA(size_t width, size_t height, bool zero_initialize = true);
        ImageRGBA(Image& img);
        ~ImageRGBA();


    public:
        uint8_t* getData() const final override;
        size_t getWidth() const final override;
        size_t getHeight() const final override;
        size_t getDataSize() const final override;
        ImageFormat getFormat() const final override;

    public:
        size_t getXStride() const final override;
        size_t getYStride() const final override;
        uint32_t turnColorToImagePixel(Color c) const final override;
        void setPixelAt(uint8_t* pos, uint32_t pix_val) final override;
        void setPixelAt(const vec2i& pos, Color c) override;

    private:
        void fromBGRA32(Image& img);
        void fromRGB24(Image& img, bool bgr);
        void fromRGB565(Image& img, bool bgr);
    };
}