#pragma once
#include <pgt/window/gui/events/Inputmanager.h>
#include "Event.h"
namespace pgt {
    class MouseButtonUpEvent : public Event {
      public:
        const int x;
        const int y;
        const PGT_KEYS button;

      public:
        MouseButtonUpEvent(int x, int y, PGT_KEYS button)
            : x(x), y(y), button(button)
        {
        }
    };
}