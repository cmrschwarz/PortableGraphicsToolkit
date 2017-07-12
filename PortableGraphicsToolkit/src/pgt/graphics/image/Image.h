#pragma once
#include <pgt/io/vfs/VirtualFileSystem.h>
#include "IImage.h"
#include <string>

struct FIBITMAP;
namespace pgt {
    class ITexture;

    class Image : public IImage {
        ImageFormat _format;
        FIBITMAP* _dib;

      public:
        explicit Image(IStreamReader& sr, const std::string& format_help = "");
        // thanks to @Incomputable @stackoverflow
        explicit Image(IStreamReader&& sr, const std::string& format_help = "")
            : Image(sr, format_help){};
        explicit Image(ITexture& t);

        ~Image();

        uint8_t* getData() const override;
        size_t getWidth() const override;
        size_t getHeight() const override;
        size_t getDataSize() const override;
        ImageFormat getFormat() const override;
        void saveImage(IStreamWriter& w);


      public:
        uint32_t turnColorToImagePixel(Color c) const override;
        void setPixelAt(uint8_t* data_pos, uint32_t pixel_val) override;
        size_t getXStride() const override;
        size_t getYStride() const override;
        void setPixelAt(const vec2i& pos, Color c) override;

      private:
        static ImageFormat getFormat(FIBITMAP* dib);
        static FIBITMAP* loadImage(IStreamReader& sr,
                                   const std::string& format_help = "");
    };
}