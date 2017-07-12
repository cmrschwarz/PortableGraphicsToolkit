#pragma once
#include <iostream>
#include "vec2i.h"

namespace pgt {
    struct vec4i {
    public:
        int x, y, z, w;

    public:
        // ctors
        vec4i();
        vec4i(int x, int y, int z, int w);
        ~vec4i();

        // copy stuff
        vec4i(const vec4i& v) = default;
        vec4i& operator=(const vec4i& v) = default;

        // non modifying ops
        vec4i operator+(const vec4i& right) const;
        vec4i operator-(const vec4i& right) const;
        vec4i operator*(int right) const;
        friend vec4i operator*(int left, const vec4i& right);

        // modifying ops
        void operator+=(const vec4i& right);
        void operator-=(const vec4i& right);
        void operator*=(int right);

        // equality
        bool operator==(const vec4i& rhs) const;

        // iostream
        friend std::ostream& operator<<(std::ostream& in, const vec4i& right);
    };
}
