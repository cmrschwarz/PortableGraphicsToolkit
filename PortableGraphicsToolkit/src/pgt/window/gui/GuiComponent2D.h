#pragma once
#include <pgt/window/gui/GuiComponent.h>
#include <pgt/window/gui/events/events.h>
namespace pgt {
    class GuiComponent2D : public GuiComponent {
      public:
        virtual void onRender(Render2DEvent& e){};
        virtual void raiseOnRender(Render2DEvent& e)
        {
            onRender(e);
            callCallback(e);
        };
    };
}