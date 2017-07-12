#pragma once
#include <pgt/window/gui/controls/RectangularControl.h>
namespace pgt {
    class DraggableControl : public RectangularControl {
    private:
        pgt::vec2i _mouse_offset;  // if positive then not dragged.
                                  // savin' byte for bool... yay


    public:
        // little reminder :)
        // bool isInBounds(const Point& p) const override = 0;

    public:
        void raiseOnMouseMoved(MouseMoveEvent& e) override;
        void raiseOnMouseButtonDown(MouseButtonDownEvent& e) override;
        void raiseOnMouseButtonUp(MouseButtonUpEvent& e) override;
    };
}