#pragma once
#include "Event.h"
namespace pgt {
    class MoveEvent : public Event {
      public:
        const int pos_x;
        const int pos_y;

      public:
        MoveEvent(int x, int y) : pos_x(x), pos_y(y)
        {
        }
    };
}