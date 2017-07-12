#pragma once
#include <string>
#include <pgt/graphics/graphics_2d_fwd.h>
#include <pgt/io/istreams/IStreamReader.h>
namespace pgt {
    class IFontManager {
    public:
        // TODO: dont take size as parameter here
        virtual void submitFont(const IFont& font) = 0;
        virtual ~IFontManager(){};
        virtual Font& getDefaultFont() = 0;
    };
}