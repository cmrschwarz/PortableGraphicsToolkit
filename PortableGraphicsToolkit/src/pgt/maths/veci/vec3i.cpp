#include "vec3i.h"

namespace pgt {
    vec3i::vec3i() : x(0), y(0), z(0)
    {
    }
    vec3i::vec3i(int x, int y, int z) : x(x), y(y), z(z)
    {
    }
    vec3i::~vec3i()
    {
    }
    vec3i operator+(vec3i left, const vec3i& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        return left;
    }
    vec3i operator-(vec3i left, const vec3i& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= left.z;
        return left;
    }
    vec3i operator*(int left, vec3i right)
    {
        right.x *= left;
        right.y *= left;
        right.z *= left;
        return right;
    }
    void vec3i::operator*=(int right)
    {
        x *= right;
        y *= right;
        z *= right;
    }

    bool vec3i::operator==(const vec3i& rhs) const
    {
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    }

    void vec3i::operator+=(const vec3i& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
    }
    void vec3i::operator-=(const vec3i& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
    }
    std::ostream& operator<<(std::ostream& in, vec3i& right)
    {
        in << "vec3i: (" << right.x << '|' << right.y << '|' << right.z << ')';
        return in;
    }
}