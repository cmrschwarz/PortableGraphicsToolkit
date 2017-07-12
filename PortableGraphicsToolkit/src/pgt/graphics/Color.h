#pragma once
#include <pgt/maths/maths.h>
namespace pgt {
    // 0xAARRGGBB
    class Color {
      public:
        static Color BLACK;
        static Color WHITE;
        static Color RED;
        static Color GREEN;
        static Color BLUE;
        static Color YELLOW;
        static Color DARK_GRAY;
        static Color GRAY;
        static Color WINDOW_BLUE;
        static Color TRANSPARENT;
        static Color LIGHT_GRAY;

      private:
        uint32_t _value;

      public:
        Color();
        Color(uint32_t argb);        // implicit on purpose
        explicit Color(vec3& rgb);   // range 0-1
        explicit Color(vec4& rgba);  // range 0-1
        Color(uint32_t r, uint32_t g, uint32_t b);
        Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

      public:
        static Color fromNetworkOrder(uint32_t no);
        static Color randomColor();
        static Color randomColor(uint8_t val);

      public:
        uint32_t toInt() const;
        uint16_t to16Bit() const;
        //(uint32_t) uint8_t[4]{A,R,G,B}
        uint32_t toNetworkOrder() const;
        vec3 toVec3() const;
        vec4 toVec4() const;
        uint32_t getR() const;
        uint32_t getG() const;
        uint32_t getB() const;
        uint32_t getA() const;

      public:
        bool operator==(Color other);
        bool operator!=(Color other);
    };
}