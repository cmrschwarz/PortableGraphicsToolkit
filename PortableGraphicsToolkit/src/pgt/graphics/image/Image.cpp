#include "Image.h"
#include "FreeImage/FreeImage.h"
#include <pgt/target_settings/target_settings.h>
#include <pgt/graphics/plattform/interface/ITexture.h>
#include <GL/glew.h>
namespace pgt {
    // TODO: make dependant on format
    Image::Image(ITexture& t)
    {
        size_t width = t.getWidth(), height = t.getHeight();
        uint8_t* buffer = new uint8_t[width * height * 3];
        t.copyData(buffer);
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGRA
        _format = ImageFormat::BGRA_32;
#else
        _format = ImageFormat::RGBA_32;
#endif

        _dib =
            FreeImage_ConvertFromRawBits(buffer, width, height, width * 3, 24,
                                         0xFF0000, 0x00FF00, 0x0000FF, false);
        delete[] buffer;
    }

    Image::Image(IStreamReader& sr, const std::string& format_help)
    {
        _dib = loadImage(sr, format_help);
        _format = getFormat(_dib);
    }

    Image::~Image()
    {
        FreeImage_Unload(_dib);
    }
    uint8_t* Image::getData() const
    {
        return FreeImage_GetBits(_dib);
    }

    size_t Image::getWidth() const
    {
        return FreeImage_GetWidth(_dib);
    }

    size_t Image::getHeight() const
    {
        return FreeImage_GetHeight(_dib);
    }

    size_t Image::getDataSize() const
    {
        return (FreeImage_GetBPP(_dib) / 8) * getWidth() * getHeight();
    }

    ImageFormat Image::getFormat() const
    {
        return _format;
    }

    ImageFormat Image::getFormat(FIBITMAP* dib)
    {
        typedef ImageFormat IMGF;
        FREE_IMAGE_TYPE fit = FreeImage_GetImageType(dib);
        if (fit != FIT_BITMAP) return IMGF::UNKNOWN;
        size_t bpp = FreeImage_GetBPP(dib);
        bool bgr = (FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR);

        switch (bpp) {
        case 8:
            return IMGF::GRAYSCALE_8;
        case 16: {
            unsigned int rm = FreeImage_GetRedMask(dib);
            unsigned int gm = FreeImage_GetGreenMask(dib);
            unsigned int bm = FreeImage_GetBlueMask(dib);
            if (gm == FI16_565_GREEN_MASK && rm == FI16_565_RED_MASK &&
                bm == FI16_565_BLUE_MASK) {
                return (bgr) ? IMGF::BGR_16_565 : IMGF::RGB_16_565;
            }
            else {
                return (bgr) ? IMGF::BGR_16_555 : IMGF::RGB_16_555;
            }
        }
        case 24:
            return (bgr) ? IMGF::BGR_24 : IMGF::RGB_24;
        case 32:
            return (bgr) ? IMGF::BGRA_32 : IMGF::RGBA_32;
        default:
            return IMGF::UNKNOWN;
        }
    }


    unsigned DLL_CALLCONV myReadProc(void* buffer, unsigned size,
                                     unsigned count, fi_handle handle)
    {
        auto& sr = *static_cast<IStreamReader*>(handle);
        size_t bytes_read = sr.read(buffer, size * count);
        return bytes_read / size;
    }

    unsigned DLL_CALLCONV myWriteProc(void* buffer, unsigned size,
                                      unsigned count, fi_handle handle)
    {
        auto& sr = *static_cast<IStreamWriter*>(handle);
        size_t siz = size * count;
        sr.write(buffer, siz);
        return siz;
    }

    int DLL_CALLCONV mySeekProc(fi_handle handle, long offset, int origin)
    {
        auto& sr = *static_cast<IStreamReader*>(handle);
        switch (origin) {
        case SEEK_SET:
            sr.setPosition(offset);
            break;
        case SEEK_CUR:
            sr.setPosition(sr.getPosition() + offset);
            break;
        case SEEK_END:
            sr.setPosition(sr.getStreamSize() + offset);
            break;
        }
        return 0;
    }

    long DLL_CALLCONV myTellProc(fi_handle handle)
    {
        auto& sr = *static_cast<IStreamReader*>(handle);
        return sr.getPosition();
    }
    void Image::saveImage(IStreamWriter& w)
    {
        FreeImageIO io;
        io.read_proc = nullptr;
        io.write_proc = myWriteProc;
        io.seek_proc = nullptr;
        io.tell_proc = nullptr;
        FreeImage_SaveToHandle(FIF_PNG, _dib, &io, (fi_handle)&w);
    }
    size_t Image::getXStride() const
    {
        PGT_ASSERT(false, "not implemented");
        return 0;
    }
    size_t Image::getYStride() const
    {
        PGT_ASSERT(false, "not implemented");
        return 0;
    }
    uint32_t Image::turnColorToImagePixel(Color c) const
    {
        PGT_ASSERT(false, "not implemented");
        return 0;
    }

    void Image::setPixelAt(uint8_t* data_pos, uint32_t pixel_val)
    {
        PGT_ASSERT(false, "not implemented");
    }

    void Image::setPixelAt(const vec2i& pos, Color c)
    {
        PGT_ASSERT(false, "not implemented");
    }

    FIBITMAP* Image::loadImage(IStreamReader& sr,
                               const std::string& format_help)
    {
        FreeImageIO io;
        io.read_proc = myReadProc;
        io.write_proc = nullptr;
        io.seek_proc = mySeekProc;
        io.tell_proc = myTellProc;
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        fif = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)&sr, 0);

        if (fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(format_help.c_str());
        PGT_ASSERT(fif != FIF_UNKNOWN, "Failed to load Image");
        FIBITMAP* dib = FreeImage_LoadFromHandle(fif, &io, (fi_handle)&sr, 0);
        PGT_ASSERT(dib, "Failed to load Image");
        return dib;
    }
}