#pragma once
#include <iostream>
namespace pgt {
    struct vec4i;

    struct vec4 {
      public:
        float x, y, z, w;

      public:
        vec4();
        explicit vec4(const vec4i& v);
        vec4(float x, float y, float z, float w);
        ~vec4();
        friend vec4 operator+(vec4 left, const vec4& right);
        friend vec4 operator-(vec4 left, const vec4& right);
        friend vec4 operator*(float left, vec4 right);
        friend vec4 operator*(vec4 left, float right)
        {
            return right * left;
        }
        void operator+=(const vec4& right);
        void operator-=(const vec4& right);
        void operator*=(float right);
        void normalize();

        friend std::ostream& operator<<(std::ostream& in, const vec4& right);
    };
}
