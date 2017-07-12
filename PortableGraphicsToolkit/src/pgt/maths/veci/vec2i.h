#pragma once
#include <iostream>
namespace pgt {
    // TODO: do changes analog to vec4i
    struct vec2i {
    public:
        int x, y;

    public:
        vec2i();
        vec2i(int x, int y);
        ~vec2i();
        friend vec2i operator+(vec2i left, const vec2i& right);
        friend vec2i operator-(vec2i left, const vec2i& right);
        friend vec2i operator*(int left, vec2i right);
        friend vec2i operator/(vec2i left, int right);

        inline friend vec2i operator*(vec2i left, int right)
        {
            return right * left;
        }
        void operator+=(const vec2i& right);
        void operator-=(const vec2i& right);
        void operator*=(int right);
        bool operator==(const vec2i& rhs) const;
        friend std::ostream& operator<<(std::ostream& in, const vec2i& right);
    };
}
