#pragma once
#include <pgt/window/gui/events/Inputmanager.h>
#include "Event.h"
namespace pgt {
    // TODO: implement modifiers mods
    class KeyDownEvent : public Event {
      public:
        const PGT_KEYS key;
        const bool repeat;

        const bool shift;
        const bool ctrl;
        const bool alt;

      public:
        KeyDownEvent(PGT_KEYS key, bool repeat, bool shift, bool ctrl, bool alt)
            : key(key), repeat(repeat), shift(shift), ctrl(ctrl), alt(alt)
        {
        }
    };
}