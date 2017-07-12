#pragma once
#include <pgt/window/gui/GuiComponent2D.h>
namespace pgt {


    class Control : public GuiComponent2D {
    private:
        Control* _parent;
        bool _enabled = true;
        bool _focused = false;
        bool _visible = true;

    public:
        virtual bool isInBounds(const vec2i& p) const = 0;
        virtual bool isInBounds(const Rectangle& r) const
        {
            return (isInBounds(vec2i(r.pos.x, r.pos.y)) &&
                    isInBounds(vec2i(r.pos.x + r.size.x, r.pos.y)) &&
                    isInBounds(vec2i(r.pos.x, r.pos.y + r.size.y)) &&
                    isInBounds(vec2i(r.pos.x + r.size.x, r.pos.y + r.size.y)));
        }
        void setParent(Control& parent)
        {
            _parent = &parent;
        }
        Control& getParent()
        {
            // TODO: maybe add check here in debug
            return *_parent;
        }

    public:
        void setVisible(bool visible)
        {
            _visible = visible;
        }
        void setEnabled(bool enabled)
        {
            _enabled = enabled;
        }
        void setFocused(bool focused, bool raise_event = true)
        {
            _focused = focused;
            if (raise_event) {
                if (_focused)
                    raiseOnFocusGained();
                else
                    raiseOnFocusLost();
            }
        }
        bool isFocused() const
        {
            return _focused;
        }
        bool isVisible() const
        {
            return _visible;
        }
        bool isEnabled() const
        {
            return _enabled;
        }
    };
};
