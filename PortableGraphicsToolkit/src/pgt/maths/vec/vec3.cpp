#include "vec3.h"
#include <pgt/maths/veci/vec3i.h>
#include <cmath>
namespace pgt {
    vec3::vec3() : x(0), y(0), z(0)
    {
    }
    vec3::vec3(float x, float y, float z) : x(x), y(y), z(z)
    {
    }
    vec3::vec3(const vec3i& v) : x((float)v.x), y(float(v.y)), z((float)v.z)
    {
    }

    vec3::~vec3()
    {
    }
    vec3 operator+(vec3 left, const vec3& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        return left;
    }
    vec3 operator-(vec3 left, const vec3& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= left.z;
        return left;
    }
    vec3 operator*(float left, vec3 right)
    {
        right.x *= left;
        right.y *= left;
        right.z *= left;
        return right;
    }
    void vec3::operator*=(float right)
    {
        x *= right;
        y *= right;
        z *= right;
    }
    void vec3::operator+=(const vec3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
    }
    void vec3::operator-=(const vec3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
    }
    void vec3::normalize()
    {
        float len = std::cbrt(x * x + y * y + z * z);
        x /= len;
        y /= len;
        z /= len;
    }
    std::ostream& operator<<(std::ostream& in, vec3& right)
    {
        in << "vec3: (" << right.x << '|' << right.y << '|' << right.z << ')';
        return in;
    }
}
