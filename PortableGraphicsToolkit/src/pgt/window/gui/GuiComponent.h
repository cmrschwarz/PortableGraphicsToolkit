#pragma once
#include "EventComponent.h"
namespace pgt {
    class GuiComponent : public EventComponent {
      public:
        virtual void onMouseMoved(MouseMoveEvent& e){};
        virtual void onMouseButtonDown(MouseButtonDownEvent& e){};
        virtual void onMouseButtonUp(MouseButtonUpEvent& e){};
        virtual void onKeyDown(KeyDownEvent& e){};
        virtual void onKeyUp(KeyUpEvent& e){};
        virtual void onTick(){};
        virtual void onFocusGained(){};
        virtual void onFocusLost(){};
        virtual void onMouseScrolled(MouseScrollEvent& e){};

      public:
        virtual void raiseOnMouseMoved(MouseMoveEvent& e)
        {
            onMouseMoved(e);
            callCallback(e);
        };
        virtual void raiseOnMouseButtonDown(MouseButtonDownEvent& e)
        {
            onMouseButtonDown(e);
            callCallback(e);
        };
        virtual void raiseOnMouseButtonUp(MouseButtonUpEvent& e)
        {
            onMouseButtonUp(e);
            callCallback(e);
        };
        virtual void raiseOnKeyDown(KeyDownEvent& e)
        {
            onKeyDown(e);
            callCallback(e);
        };
        virtual void raiseOnKeyUp(KeyUpEvent& e)
        {
            onKeyUp(e);
            callCallback(e);
        };
        virtual void raiseOnTick()
        {
            onTick();
            callCallback(TickEvent());
        };
        virtual void raiseOnFocusGained()
        {
            onFocusGained();
            callCallback(FocusGainedEvent());
        };
        virtual void raiseOnFocusLost()
        {
            onFocusLost();
            callCallback(FocusLostEvent());
        };
        virtual void raiseOnMouseScrolled(MouseScrollEvent& e)
        {
            onMouseScrolled(e);
            callCallback(e);
        }
    };
}
