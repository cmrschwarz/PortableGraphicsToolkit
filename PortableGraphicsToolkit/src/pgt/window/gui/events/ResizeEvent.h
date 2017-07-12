#pragma once
#include "Event.h"
#include <pgt/maths/maths.h>
namespace pgt {
    class ResizeEvent : public Event {
    public:
        const vec2i size_new;

    public:
        ResizeEvent(const vec2i& sn) : size_new(sn)
        {
        }
    };
}