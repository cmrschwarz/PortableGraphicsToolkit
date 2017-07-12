#include "Panel.h"
#include <pgt/graphics/plattform/opengl/2d/GlRenderer2D.h>
namespace pgt {
    Panel::Panel():_focused(nullptr)
    {
    }
    bool Panel::getsClickPreview() const
    {
        return _click_preview;
    }
    bool Panel::getsKeyPreview() const
    {
        return _key_preview;
    }
    void Panel::setKeyPreview(bool kp)
    {
        _key_preview = kp;
    }
    void Panel::setClickPreview(bool cp)
    {
        _click_preview = cp;
    }

    void Panel::addControl(Control& c)
    {
        addComponent(c);
        c.setParent(*this);
    }

    void Panel::removeControl(Control& c)
    {
        removeComponent(c);
    }

    void Panel::setFocused(Control& c)
    {
        _focused = &c;
    }

    void Panel::raiseOnRender(Render2DEvent& e)
    {
        // TODO: cache this
        e.renderer.pushViewport(_bounds.pos, _bounds.size);
        ContainerBase_t::raiseOnRender(e);
        forwardEvent(&ContainerComponent_t::raiseOnRender, e);
        e.renderer.popViewport();
    }
    void Panel::raiseOnMouseButtonDown(MouseButtonDownEvent& e)
    {
        MouseButtonDownEvent en(e.x - getBounds().pos.x,
                                e.y - getBounds().pos.y, e.button);
        if (_click_preview) {
            ContainerBase_t::raiseOnMouseButtonDown(e);
        }
        for (auto rit = _components.rbegin(); rit != _components.rend();
             ++rit) {
            if ((*rit)->isInBounds(vec2i(en.x, en.y))) {
                (*rit)->raiseOnMouseButtonDown(en);
                if (_focused) {
                    _focused->setFocused(false);
                }
                _focused = *rit;
                _focused->setFocused(true);
                return;
            }
        }
        if (_focused) {
            _focused->setFocused(false);
            _focused = nullptr;
        }

        if (!_click_preview) ContainerBase_t::raiseOnMouseButtonDown(e);
    }
    void Panel::raiseOnMouseButtonUp(MouseButtonUpEvent& e)
    {
        if (_click_preview) {
            ContainerBase_t::raiseOnMouseButtonUp(e);
        }
        if (_focused != nullptr) {
            _focused->raiseOnMouseButtonUp(e);
        }
        else {
            if (!_click_preview) ContainerBase_t::raiseOnMouseButtonUp(e);
        }
    }
    void Panel::raiseOnKeyDown(KeyDownEvent& e)
    {
        if (_key_preview || _focused == nullptr) {
            ContainerBase_t::raiseOnKeyDown(e);
        }
        if (_focused != nullptr) {
            _focused->raiseOnKeyDown(e);
        }
    }
    void Panel::raiseOnKeyUp(KeyUpEvent& e)
    {
        if (_key_preview || _focused == nullptr) {
            ContainerBase_t::raiseOnKeyUp(e);
        }
        if (_focused != nullptr) {
            _focused->raiseOnKeyUp(e);
        }
    }

    void Panel::raiseOnMouseScrolled(MouseScrollEvent& e)
    {
        ContainerBase_t::raiseOnMouseScrolled(e);
        if (_focused != nullptr) _focused->raiseOnMouseScrolled(e);
    }

    void Panel::raiseOnFocusGained()
    {
        ContainerBase_t::raiseOnFocusGained();
    }

    void Panel::raiseOnFocusLost()
    {
        ContainerBase_t::raiseOnFocusGained();
    }
}