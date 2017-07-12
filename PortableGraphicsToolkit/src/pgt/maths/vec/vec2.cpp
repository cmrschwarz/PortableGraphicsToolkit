#include "vec2.h"
#include <pgt/maths/veci/vec2i.h>
#include <cmath>
namespace pgt {
    vec2::vec2() : x(0), y(0)
    {
    }
    vec2::vec2(float x, float y) : x(x), y(y)
    {
    }

    vec2::vec2(const vec2i& v) : x((float)v.x), y(float(v.y))
    {
    }

    vec2::~vec2()
    {
    }
    vec2 operator+(vec2 left, const vec2& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }
    vec2 operator-(vec2 left, const vec2& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }
    vec2 operator*(float left, vec2 right)
    {
        right.x *= left;
        right.y *= left;
        return right;
    }
    void vec2::operator*=(float right)
    {
        x *= right;
        y *= right;
    }
    void vec2::operator+=(const vec2& right)
    {
        x += right.x;
        y += right.y;
    }
    void vec2::operator-=(const vec2& right)
    {
        x -= right.x;
        y -= right.y;
    }
    void vec2::normalize()
    {
        float len = std::sqrt(x * x + y * y);
        x /= len;
        y /= len;
    }
    std::ostream& operator<<(std::ostream& in, const vec2& right)
    {
        in << "vec2: (" << right.x << '|' << right.y << ')';
        return in;
    }
}