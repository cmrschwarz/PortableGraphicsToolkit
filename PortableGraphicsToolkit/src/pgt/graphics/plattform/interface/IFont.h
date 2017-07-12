#pragma once
#include <pgt/maths/maths.h>
#include <string>
namespace pgt {
    class IFont {
    public:
        virtual const std::string& getName() const = 0;
        virtual size_t getSize() const = 0;
        virtual vec3i measureString(const std::string& text) const = 0;
    };
}