#pragma once
#include <iostream>
namespace pgt {
	//TODO: do changes analog to vec4i
    struct vec3i {
    public:
        int x, y, z;

    public:
        vec3i();
        vec3i(int x, int y, int z);
        ~vec3i();
        friend vec3i operator+(vec3i left, const vec3i& right);
        friend vec3i operator-(vec3i left, const vec3i& right);
        friend vec3i operator*(int left, vec3i right);
        inline friend vec3i operator*(vec3i left, int right)
        {
            return right * left;
        }
        void operator+=(const vec3i& right);
        void operator-=(const vec3i& right);
        void operator*=(int right);
        bool operator==(const vec3i& rhs) const;
        friend std::ostream& operator<<(std::ostream& in, const vec3i& right);
    };
}
