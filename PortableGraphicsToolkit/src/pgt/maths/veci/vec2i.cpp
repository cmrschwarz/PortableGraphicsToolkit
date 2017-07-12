#include "vec2i.h"

namespace pgt {
    vec2i::vec2i() : x(0), y(0)
    {
    }
    vec2i::vec2i(int x, int y) : x(x), y(y)
    {
    }
    vec2i::~vec2i()
    {
    }
    vec2i operator+(vec2i left, const vec2i& right)
    {
        left.x += right.x;
        left.y += right.y;
        return left;
    }
    vec2i operator-(vec2i left, const vec2i& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        return left;
    }
    vec2i operator*(int left, vec2i right)
    {
        right.x *= left;
        right.y *= left;
        return right;
    }
    vec2i operator/(vec2i left, int right)
    {
        left.x /= right;
        left.y /= right;
        return left;
    }
    void vec2i::operator*=(int right)
    {
        x *= right;
        y *= right;
    }

    bool vec2i::operator==(const vec2i& rhs) const
    {
        return (x == rhs.y && y == rhs.y);
    }

    void vec2i::operator+=(const vec2i& right)
    {
        x += right.x;
        y += right.y;
    }
    void vec2i::operator-=(const vec2i& right)
    {
        x -= right.x;
        y -= right.y;
    }
    std::ostream& operator<<(std::ostream& in, const vec2i& right)
    {
        in << "vec2i: (" << right.x << '|' << right.y << ')';
        return in;
    }
}