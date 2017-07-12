#pragma once
#include <pgt/window/gui/events/Inputmanager.h>
#include "Event.h"
namespace pgt {
    class MouseScrollEvent : public Event {
      public:
        const int scroll;

      public:
        MouseScrollEvent(int scroll) : scroll(scroll)
        {
        }
    };
}