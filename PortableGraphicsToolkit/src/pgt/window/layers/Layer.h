#pragma once
#include <pgt/window/gui/GuiComponent.h>
namespace pgt {
    class Layer : public GuiComponent {
      public:
        virtual void onMove(MoveEvent& e){};
        virtual void onResize(ResizeEvent& e){};

        virtual void raiseOnMove(MoveEvent& e)
        {
            onMove(e);
            callCallback(e);
        };
        virtual void raiseOnResize(ResizeEvent& e)
        {
            onResize(e);
            callCallback(e);
        };
    };
  
}