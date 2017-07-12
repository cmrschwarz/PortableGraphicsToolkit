#pragma once
#include <iostream>
namespace pgt {
    struct vec2i;

    struct vec2 {
      public:
        float x, y;

      public:
        vec2();
        explicit vec2(const vec2i& v);
        vec2(float x, float y);
        ~vec2();
        friend vec2 operator+(vec2 left, const vec2& right);
        friend vec2 operator-(vec2 left, const vec2& right);
        friend vec2 operator*(float left, vec2 right);
        inline friend vec2 operator*(vec2 left, float right)
        {
            return right * left;
        }
        void operator+=(const vec2& right);
        void operator-=(const vec2& right);
        void operator*=(float right);
        void normalize();

        friend std::ostream& operator<<(std::ostream& in, const vec2& right);
    };
}
