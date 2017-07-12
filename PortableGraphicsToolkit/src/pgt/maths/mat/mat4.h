#pragma once
#include <iostream>
#include "..\maths.h"
namespace pgt {
    struct vec3;
    struct mat4 {
      public:
        float elements[4 * 4];

      public:
        mat4();
        mat4(float diagonal);
        ~mat4();
        float& getElement(int x, int y);
        float getElement(int x, int y) const;
        friend std::ostream& operator<<(std::ostream& left, const mat4& right);
        friend mat4 operator*(const mat4& left, const mat4& right);
        friend vec3 operator*(const mat4& left,
                              const vec3& right);  // screw maths xD
        friend vec4 operator*(const mat4& left, const vec4& right);
        void operator*=(const mat4& right);
        static mat4 identity();
        static mat4 scale(const vec3& scale);
        static mat4 translation(const vec3& translation);
        static mat4 rotation(float angle, const vec3& axis);
        static mat4 perspective(float nearPlane, float farPlane, float fovX,
                                float aspect_ratio);
        static mat4 orthographic(float left, float right, float bottom,
                                 float top, float near, float far);
    };
}
