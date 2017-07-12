#pragma once
#include "Control.h"
#include <pgt/window/gui/Rectangle.h>
namespace pgt {

    class RectangularControl : public Control {
    protected:
        Rectangle _bounds;

    public:
        virtual void onResize(ResizeEvent& e){};
        virtual void raiseOnResize(ResizeEvent& e)
        {
            onResize(e);
            callCallback(e);
        }
        virtual void onPositionChanged(PositionChangedEvent& e){};
        virtual void raiseOnPositionChanged(PositionChangedEvent& e)
        {
            onPositionChanged(e);
            callCallback(e);
        };
        bool isInBounds(const vec2i& p) const override
        {
            return _bounds.contains(p);
        }
        bool isInBounds(const Rectangle& r) const override
        {
            // TODO: maybe provide optimized impl here
            return Control::isInBounds(r);
        }
        const Rectangle& getBounds() const
        {
            return _bounds;
        }
        void setBounds(const Rectangle& r, bool raise_event = true)
        {
            if (raise_event) {
                Rectangle r2 = r;
                _bounds = r;
                if (!(r2.size == _bounds.pos)) {
                    ResizeEvent re(r.size);
                    raiseOnResize(re);
                }
                if (!(r2.pos == _bounds.size)) {
                    PositionChangedEvent pce(r.pos);
                    raiseOnPositionChanged(pce);
                }
            }
            else {
                _bounds = r;
            }
        }
    };
}