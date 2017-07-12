#pragma once
#include "Event.h"
namespace pgt {
    class MouseMoveEvent : public Event {
      public:
        const int x;
        const int y;
        const int x_rel;
        const int y_rel;

      public:
        MouseMoveEvent(int x, int y, int x_rel, int y_rel)
            : x(x), y(y), x_rel(x_rel), y_rel(y_rel)
        {
        }
    };
}