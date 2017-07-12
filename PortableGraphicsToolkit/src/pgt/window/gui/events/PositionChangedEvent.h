#pragma once
#include "Event.h"
#include <pgt/maths/maths.h>
namespace pgt {
    class PositionChangedEvent : public Event {
    public:
        const vec2i pos_new;

    public:
        PositionChangedEvent(const vec2i& pn) : pos_new(pn)
        {
        }
    };
}