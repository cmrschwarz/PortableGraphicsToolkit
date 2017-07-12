#pragma once
#include "Event.h"
namespace pgt {
    class TickEvent : public Event {
    };
    class RenderEvent : public Event {
    };
    class WindowCloseEvent : public Event {
    };
    class FocusGainedEvent : public Event {
    };
    class FocusLostEvent : public Event {
    };
}