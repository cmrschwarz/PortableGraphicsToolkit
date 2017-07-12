#pragma once
#include <pgt/window/gui/events/events.h>
#include <pgt/graphics/graphics_2d_fwd.h>
namespace pgt {
    class Render2DEvent : public Event {
      public:
        Renderer2D& renderer;
        Render2DEvent(Renderer2D& rndr) : renderer(rndr)
        {
        }
    };
}