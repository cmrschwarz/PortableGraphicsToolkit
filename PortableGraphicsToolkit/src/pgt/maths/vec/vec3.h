#pragma once
#include <iostream>
namespace pgt {
    struct vec3i;

    struct vec3 {
      public:
        float x, y, z;

      public:
        vec3();
        explicit vec3(const vec3i& v);
        vec3(float x, float y, float z);
        ~vec3();
        friend vec3 operator+(vec3 left, const vec3& right);
        friend vec3 operator-(vec3 left, const vec3& right);
        friend vec3 operator*(float left, vec3 right);
        inline friend vec3 operator*(vec3 left, float right)
        {
            return right * left;
        }
        void operator+=(const vec3& right);
        void operator-=(const vec3& right);
        void operator*=(float right);
        void normalize();

        friend std::ostream& operator<<(std::ostream& in, const vec3& right);
    };
}
