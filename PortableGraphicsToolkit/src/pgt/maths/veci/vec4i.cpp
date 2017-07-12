#include "vec4i.h"

namespace pgt {
    vec4i::vec4i() : x(0), y(0), z(0), w(0)
    {
    }
    vec4i::vec4i(int x, int y, int z, int w) : x(x), y(y), z(z), w(w)
    {
    }
    vec4i::~vec4i()
    {
    }

    vec4i vec4i::operator+(const vec4i& right) const
    {
        vec4i left = (*this);
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;
        left.w += right.w;
        return left;
    }
    vec4i vec4i::operator-(const vec4i& right) const
    {
        vec4i left = (*this);
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;
        left.w -= right.w;
        return left;
    }
    vec4i vec4i::operator*(int left) const
    {
        vec4i right = (*this);
        right.x *= left;
        right.y *= left;
        right.z *= left;
        right.w *= left;
        return right;
    }

    void vec4i::operator*=(int right)
    {
        x *= right;
        y *= right;
        z *= right;
        w *= right;
    }

    void vec4i::operator+=(const vec4i& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;
    }

    void vec4i::operator-=(const vec4i& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;
    }

    bool vec4i::operator==(const vec4i& rhs) const
    {
        return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
    }

    std::ostream& operator<<(std::ostream& in, const vec4i& right)
    {
        in << "vec4i: (" << right.x << '|' << right.y << '|' << right.z << '|'
           << right.w << ')';
        return in;
    }
}