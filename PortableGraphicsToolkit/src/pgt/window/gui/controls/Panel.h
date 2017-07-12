#pragma once
#include "RectangularControl.h"
#include "ControlContainer.h"
namespace pgt {
    //!! this scraps some modification to raise() done by superclasses as it
    // doesnt call super::raise(e) for certain events
    class Panel : public ControlContainer<RectangularControl, Control> {
    private:
        bool _click_preview;
        bool _key_preview;
        Control* _focused;

    public:
        Panel();
        bool getsClickPreview() const;
        bool getsKeyPreview() const;
        void setKeyPreview(bool kp);
        void setClickPreview(bool cp);
        void addControl(Control& c);
        void removeControl(Control& c);
        void setFocused(Control& c);

    public:
        void raiseOnRender(Render2DEvent& e) override;
        void raiseOnMouseButtonDown(MouseButtonDownEvent& e) override;
        void raiseOnKeyDown(KeyDownEvent& e) override;
        void raiseOnMouseButtonUp(MouseButtonUpEvent& e) override;
        void raiseOnKeyUp(KeyUpEvent& e) override;
        void raiseOnMouseScrolled(MouseScrollEvent& e) override;
        void raiseOnFocusGained() override;
        void raiseOnFocusLost() override;
    };
}