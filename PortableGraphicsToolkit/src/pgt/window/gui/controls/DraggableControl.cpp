#include "DraggableControl.h"

namespace pgt {


    void DraggableControl::raiseOnMouseMoved(MouseMoveEvent& e)
    {
        if (_mouse_offset.x < 0) {
            Rectangle r = getBounds();
            r.pos.x = e.x + _mouse_offset.x;
            r.pos.y = e.y + _mouse_offset.y;
            setBounds(r);
        }
        RectangularControl::raiseOnMouseMoved(e);
    }

    void DraggableControl::raiseOnMouseButtonUp(MouseButtonUpEvent& e)
    {
        _mouse_offset.x = 1;
        RectangularControl::raiseOnMouseButtonUp(e);
    }

    void DraggableControl::raiseOnMouseButtonDown(MouseButtonDownEvent& e)
    {
        const Rectangle& r = getBounds();
        _mouse_offset = pgt::vec2i(r.pos.x - e.x, r.pos.y - e.y);
        RectangularControl::raiseOnMouseButtonDown(e);
    }
}
