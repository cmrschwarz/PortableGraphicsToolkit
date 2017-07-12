#pragma once
#include <iostream>
#include "..\maths.h"
namespace pgt {
    struct vec2;
    class mat3 {
      public:
        float elements[3 * 3];  // could be in union with columns but i have
                                // GET_ELEMENT <-- does the job
      public:
        mat3();
        mat3(float identity);
        ~mat3();
        float& getElement(int x, int y);
        float getElement(int x, int y) const;
        friend std::ostream& operator<<(std::ostream& left, const mat3& right);
        friend mat3 operator*(const mat3& left, const mat3& right);
        friend vec2 operator*(const mat3& left,
                              const vec2& right);  // screw maths xD
        friend vec3 operator*(const mat3& left, const vec3& right);
        void operator*=(const mat3& right);
        static mat3 identity();
        static mat3 scale(const vec2& scale);
        static mat3 translation(const vec2& translation);
        static mat3 rotation(float angle, const vec2& axis);
        static mat3 projection(float left, float right, float top,
                               float bottom);
    };
}
