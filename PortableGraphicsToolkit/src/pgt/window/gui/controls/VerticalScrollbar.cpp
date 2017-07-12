#include "VerticalScrollbar.h"
#include <pgt/graphics/graphics_2d.h>

namespace pgt {

    VerticalScrollbar::VerticalScrollbar()
    {
    }

    void VerticalScrollbar::onResize(ResizeEvent& e)
    {
        updateBarBounds();
    }

    void VerticalScrollbar::onRender(Render2DEvent& e)
    {
        if (!isVisible()) return;
        e.renderer.setColor(Color::DARK_GRAY);
        e.renderer.fillRectangle(getBounds().pos, getBounds().size);
        if (_max_scroll > 0) {
            if (_dragged_y == -2) {
                e.renderer.setColor(Color::GRAY);
            }
            else if (_dragged_y == -1) {
                e.renderer.setColor(Color::LIGHT_GRAY);
            }
            else {
                e.renderer.setColor(Color::WHITE);
            }

            e.renderer.fillRectangle(_bar.pos, _bar.size);
        }
    }

    void VerticalScrollbar::onMouseButtonDown(MouseButtonDownEvent& e)
    {
        if (!_bar.contains(vec2i(e.x, e.y))) {
            _bar.pos.y = clampBarPos(e.y - _bar.size.y / 2);
            updateScrollValue();
        }
        _dragged_y = e.y - _bar.pos.y;
    }

    void VerticalScrollbar::onMouseButtonUp(MouseButtonUpEvent& e)
    {
        if (_dragged_y >= 0) {
            if (_bar.contains(vec2i(e.x, e.y))) {
                _dragged_y = -1;
            }
            else {
                _dragged_y = -2;
            }
        }
    }

    void VerticalScrollbar::onMouseMoved(MouseMoveEvent& e)
    {
        if (_dragged_y >= 0) {
            const Rectangle& bnds = getBounds();
            _bar.pos.y = clampBarPos(e.y - _dragged_y);
            updateScrollValue();
        }
        else {
            if (_bar.contains(vec2i(e.x, e.y))) {
                _dragged_y = -1;
            }
            else {
                _dragged_y = -2;
            }
        }
    }

    void VerticalScrollbar::onMouseScrolled(MouseScrollEvent& e)
    {
        _scroll_value = pgt::clamp(_scroll_value + e.scroll, 0, _max_scroll);
        updateBarPos();
    }

    void VerticalScrollbar::setMaxScroll(int max)
    {
        _max_scroll = (max > 0) ? max : 0;
        _scroll_value = pgt::clamp(_scroll_value, 0, _max_scroll);
        updateBarPos();
    }

    void VerticalScrollbar::setBarPercentage(float bar_percentage)
    {
        _bar_percentage = bar_percentage;
        updateBarBounds();
    }

    int VerticalScrollbar::getValue() const
    {
        return _scroll_value;
    }

    void VerticalScrollbar::setValue(int val)
    {
        _scroll_value = val;
    }

    void VerticalScrollbar::updateBarBounds()
    {
        Rectangle bnds = getBounds();
        _bar.pos.x = bnds.pos.x + _border_width;
        _bar.size.x = bnds.size.x - _border_width * 2;
        _bar.size.y = _bar_percentage * (bnds.size.y - _border_width * 2);
        updateBarPos();
    }

    void VerticalScrollbar::updateBarPos()
    {
        _bar.pos.y = getBounds().pos.y + _border_width +
                     (((float)_scroll_value) / _max_scroll) *
                         (getBounds().size.y - _bar.size.y - _border_width * 2);
    }

    void VerticalScrollbar::updateScrollValue()
    {
        _scroll_value =
            (((float)(_bar.pos.y - getBounds().pos.y - _border_width) /
              (getBounds().size.y - _bar.size.y - _border_width * 2))) *
            _max_scroll;
    }

    int VerticalScrollbar::clampBarPos(int pos_y)
    {
        return pgt::clamp(pos_y, getBounds().pos.y + _border_width,
                         getBounds().pos.y + getBounds().size.y - _bar.size.y -
                             _border_width);
    }
}
