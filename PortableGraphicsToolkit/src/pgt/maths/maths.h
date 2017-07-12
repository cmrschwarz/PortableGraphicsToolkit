#pragma once
#include "pgt/maths/vec/vec2.h"
#include "pgt/maths/vec/vec3.h"
#include "pgt/maths/vec/vec4.h"
#include "pgt/maths/veci/vec2i.h"
#include "pgt/maths/veci/vec3i.h"
#include "pgt/maths/veci/vec4i.h"
#include "pgt/maths/mat/mat3.h"
#include "pgt/maths/mat/mat4.h"
#define _USE_MATH_DEFINES
#include <math.h>
namespace pgt {
    static const double PI = M_PI;
    float toRadians(float degrees);
    template <typename TYPE>
    inline TYPE clamp(TYPE val, TYPE min, TYPE max)
    {
        if (val < min) val = min;
        if (val > max) val = max;
        return val;
    }
    template <typename TYPE>
    inline TYPE min(TYPE val1, TYPE val2)
    {
        if (val1 < val2) return val1;
        return val2;
    }
    template <typename TYPE>
    inline TYPE max(TYPE val1, TYPE val2)
    {
        if (val1 > val2) return val1;
        return val2;
    }
}