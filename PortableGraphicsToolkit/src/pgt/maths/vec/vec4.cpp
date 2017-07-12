#include "vec4.h"
#include <pgt/maths/veci/vec4i.h>
#include <cmath>
namespace pgt {
    vec4::vec4() : x(0), y(0), z(0), w(0)
    {
    }
    vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
    {
    }

    vec4::vec4(const vec4i& v)
        : x((float)v.x), y(float(v.y)), z((float)v.z), w((float)v.w)
    {
    }

    vec4::~vec4()
    {
    }
    vec4 operator+(vec4 left, const vec4& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        left.w += right.w;
        return left;
    }
    vec4 operator-(vec4 left, const vec4& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;
        left.w -= right.w;
        return left;
    }
    vec4 operator*(float left, vec4 right)
    {
        right.x *= left;
        right.y *= left;
        right.z *= left;
        right.w *= left;
        return right;
    }
    void vec4::operator*=(float right)
    {
        x *= right;
        y *= right;
        z *= right;
        w *= right;
    }
    void vec4::operator+=(const vec4& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;
    }
    void vec4::operator-=(const vec4& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;
    }
    void vec4::normalize()
    {
        float len = std::pow(x * x + y * y + z * z + w * w, 0.25);
        x /= len;
        y /= len;
        z /= len;
        w /= len;
    }
    std::ostream& operator<<(std::ostream& in, const vec4& right)
    {
        in << "vec4: (" << right.x << '|' << right.y << '|' << right.z << '|'
           << right.w << ')';
        return in;
    }
}