#include "mat3.h"
#include <pgt/maths/maths.h>
#include <memory.h>
#define GET_ELEMENT(matrix, x, y)                                              \
    (matrix)._elements[(y) + (x)*4]  // turning Row major (x,y) to Column Major
                                     // (open gl)
namespace pgt {
    mat3::mat3()
    {
        memset(elements, 0, sizeof(elements));
    }
    mat3::mat3(float identity) : mat3()
    {
        getElement(0, 0) = identity;
        getElement(1, 1) = identity;
        getElement(2, 2) = identity;
    }
    mat3 mat3::identity()
    {
        return mat3(1.0f);
    }
    mat3::~mat3()
    {
    }
    float& mat3::getElement(int x, int y)
    {
        return elements[y + x * 3];
    }

    float mat3::getElement(int x, int y) const
    {
        return elements[y + x * 3];
    }
    std::ostream& operator<<(std::ostream& left, const mat3& right)
    {
        left << "mat3:" << std::endl;
        for (int y = 0; y < 3; y++) {
            left << "|";
            for (int x = 0; x < 3; x++) {
                left << right.getElement(x, y) << '|';
            }
            left << std::endl;
        }
        return left;
    }

    void mat3::operator*=(const mat3& right)
    {
        memcpy(elements, (*this * right).elements, sizeof(elements));
    }
    mat3 operator*(const mat3& left, const mat3& right)
    {
        mat3 res = mat3();
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int i = 0; i < 3; i++) {
                    res.getElement(x, y) +=
                        left.getElement(i, y) * right.getElement(x, i);
                }
            }
        }
        return res;
    }
    vec2 operator*(const mat3& left, const vec2& right)
    {
        vec2 res;
        res.x = left.getElement(0, 0) * right.x +
                left.getElement(1, 0) * right.y + left.getElement(2, 0);
        res.y = left.getElement(0, 1) * right.x +
                left.getElement(1, 1) * right.y + left.getElement(2, 1);
        return res;
    }
    vec3 operator*(const mat3& left, const vec3& right)
    {
        vec3 res;
        res.x = left.getElement(0, 0) * right.x +
                left.getElement(1, 0) * right.y +
                left.getElement(2, 0) * right.z;
        res.y = left.getElement(0, 1) * right.x +
                left.getElement(1, 1) * right.y +
                left.getElement(2, 1) * right.z;
        res.z = left.getElement(0, 2) * right.x +
                left.getElement(1, 2) * right.y +
                left.getElement(2, 2) * right.z;
        return res;
    }
    mat3 mat3::scale(const vec2& scale)
    {
        mat3 ret;
        ret.getElement(0, 0) = scale.x;
        ret.getElement(1, 1) = scale.y;
        ret.getElement(2, 2) = 1.0f;
        return ret;
    }
    mat3 mat3::translation(const vec2& translation)
    {
        mat3 ret = mat3(1.0f);
        ret.getElement(2, 0) = translation.x;
        ret.getElement(2, 1) = translation.y;
        return ret;
    }
    mat3 mat3::rotation(float angle, const vec2& axis)
    {
        // TODO. will be fun:)
        return mat3();
    }
    mat3 mat3::projection(float left, float right, float top, float bottom)
    {
        mat3 ret;
        ret.getElement(0, 0) = 2.0f / (right - left);
        ret.getElement(1, 1) = 2.0f / (top - bottom);
        ret.getElement(2, 2) = 1.0f;
        ret.getElement(2, 0) = (left + right) / (left - right);
        ret.getElement(2, 1) = (bottom + top) / (bottom - top);
        return ret;
    }
}
