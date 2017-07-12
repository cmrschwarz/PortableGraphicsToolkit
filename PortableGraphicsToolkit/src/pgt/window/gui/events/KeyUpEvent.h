#pragma once
#include <pgt/window/gui/events/Inputmanager.h>
#include "Event.h"
namespace pgt {
    // TODO: implement modifiers mods
    class KeyUpEvent : public Event {
      public:
        const PGT_KEYS key;

        const bool shift;
        const bool ctrl;
        const bool alt;

      public:
        KeyUpEvent(PGT_KEYS key, bool shift, bool ctrl, bool alt)
            : key(key), shift(shift), ctrl(ctrl), alt(alt)
        {
        }
    };
}