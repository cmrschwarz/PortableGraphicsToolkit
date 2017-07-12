#pragma once
#include "RectangularControl.h"
#include <pgt/graphics/COlor.h>
namespace pgt {
    class ListViewItemRenderEvent : public Render2DEvent {
      public:
        vec2i pos;
        const vec2i size;
        ListViewItemRenderEvent(Renderer2D& r, vec2i size)
            : pos(), size(size), Render2DEvent(r)
        {
        }
    };
    class ListViewItem : public GuiComponent {
      private:
        Color _color;

      public:
        ListViewItem();
        virtual void raiseOnRender(ListViewItemRenderEvent& e);
        virtual void onRender(ListViewItemRenderEvent& e);
    };
}