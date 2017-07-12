#include "Color.h"
#include <pgt/target_settings/target_settings.h>
namespace pgt {
    Color::Color()
    {
    }

    Color::Color(uint32_t argb) : _value(argb)
    {
    }

    Color::Color(vec3& rgb)
        : Color((int)(rgb.x * 255.0), (int)(rgb.y * 255.0),
                (int)(rgb.z * 255.0))
    {
    }

    Color::Color(vec4& rgba)
        : Color((int)(rgba.x * 255.0), (int)(rgba.y * 255.0),
                (int)(rgba.z * 255.0), (int)(rgba.w * 255.0))
    {
    }
    Color::Color(uint32_t r, uint32_t g, uint32_t b) : Color(r, g, b, 255)
    {
    }

    Color::Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
    {
        _value = b;
        _value |= g << 8;
        _value |= r << 16;
        _value |= a << 24;
    }

    Color Color::fromNetworkOrder(uint32_t no)
    {
#if PGT_LITTLE_ENDIAN
        // alpha and green are correctly positioned, red and blue need to be
        // switched
        return Color(no & 0xFF00FF00 | ((no & 0xFF) << 16) |
                     ((no & 0xFF0000) >> 16));
#else
#if PGT_BIG_ENDIAN
        return Color(no);
#else
#error Please only use plattforms that are either big or little endian
#endif
#endif
    }

    Color Color::randomColor()
    {
        return Color(std::rand() % 255, std::rand() % 255, std::rand() % 255);
    }

    Color Color::randomColor(uint8_t val)
    {
        static Color clrs[]{RED,
                            GREEN,
                            BLUE,
                            YELLOW,
                            Color(200, 100, 10),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor(),
                            randomColor()};
        return clrs[val % (sizeof(clrs) / sizeof(Color))];
    }

    // Color::Color(const Color& other) : _value(other._value){ }

    uint32_t Color::toInt() const
    {
        return _value;
    }

    uint16_t Color::to16Bit() const
    {
        return ((getR() >> 3) << 11) | ((getG() >> 2) << 5) | ((getB() >> 3));
    }

    uint32_t Color::toNetworkOrder() const
    {
#if PGT_LITTLE_ENDIAN
        // alpha and green are correctly positioned, red and blue need to be
        // switched
        return _value & 0xFF00FF00 | (getB() << 16) | getR();
#else
#if PGT_BIG_ENDIAN
        return _value;
#else
#error Please only use plattforms that are either big or little endian
#endif
#endif
    }

    vec3 Color::toVec3() const
    {
        vec3 ret_val;
        ret_val.x = ((float)getR()) / 255.0;
        ret_val.y = ((float)getG()) / 255.0;
        ret_val.z = ((float)getB()) / 255.0;
        return ret_val;
    }
    vec4 Color::toVec4() const
    {
        vec4 ret_val;
        ret_val.x = ((float)getR()) / 255.0;
        ret_val.y = ((float)getG()) / 255.0;
        ret_val.z = ((float)getB()) / 255.0;
        ret_val.w = ((float)getA()) / 255.0;
        return ret_val;
    }
    uint32_t Color::getR() const
    {
        return (_value & (0xFF0000)) >> 16;
    }
    uint32_t Color::getG() const
    {
        return (_value & (0xFF00)) >> 8;
    }
    uint32_t Color::getB() const
    {
        return _value & (0xFF);
    }
    uint32_t Color::getA() const
    {
        return (_value & (0xFF000000)) >> 24;
    }

    bool Color::operator!=(Color other)
    {
        return other._value != _value;
    }

    bool Color::operator==(Color other)
    {
        return other._value == _value;
    }
#define CCONST(NAME, HEX) Color Color::NAME(HEX);
    CCONST(BLACK, 0xFF000000);
    CCONST(WHITE, 0xFFFFFFFF);
    CCONST(RED, 0xFFFF0000);
    CCONST(GREEN, 0xFF00FF00);
    CCONST(BLUE, 0xFF0000FF);
    CCONST(YELLOW, 0xFFFFFF00);
    CCONST(DARK_GRAY, 0xFF202020);
    CCONST(GRAY, 0xFF666666);
    CCONST(LIGHT_GRAY, 0xFF888888);
    CCONST(WINDOW_BLUE, 0xFF2B83FF);
    CCONST(TRANSPARENT, 0x000000);
#undef CCONST
}