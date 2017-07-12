#include "HorizontalScrollbar.h"
#include <pgt/graphics/graphics_2d.h>

namespace pgt {

    HorizontalScrollbar::HorizontalScrollbar()
    {
    }

    void HorizontalScrollbar::onResize(ResizeEvent& e)
    {
        updateBarBounds();
    }

    void HorizontalScrollbar::onRender(Render2DEvent& e)
    {
        if (!isVisible()) return;
        e.renderer.setColor(Color::DARK_GRAY);
        e.renderer.fillRectangle(getBounds().pos, getBounds().size);
        if (_max_scroll > 0) {
            if (_dragged_x == -2) {
                e.renderer.setColor(Color::GRAY);
            }
            else if (_dragged_x == -1) {
                e.renderer.setColor(Color::LIGHT_GRAY);
            }
            else {
                e.renderer.setColor(Color::WHITE);
            }

            e.renderer.fillRectangle(_bar.pos, _bar.size);
        }
    }

    void HorizontalScrollbar::onMouseButtonDown(MouseButtonDownEvent& e)
    {
        if (!_bar.contains(vec2i(e.x, e.y))) {
            _bar.pos.x = clampBarPos(e.x - _bar.size.x / 2);
            updateScrollValue();
        }
        _dragged_x = e.x - _bar.pos.x;
    }

    void HorizontalScrollbar::onMouseButtonUp(MouseButtonUpEvent& e)
    {
        if (_dragged_x >= 0) {
            if (_bar.contains(vec2i(e.x, e.y))) {
                _dragged_x = -1;
            }
            else {
                _dragged_x = -2;
            }
        }
    }


    void HorizontalScrollbar::onMouseMoved(MouseMoveEvent& e)
    {
        if (_dragged_x >= 0) {
            const Rectangle& bnds = getBounds();
            _bar.pos.x = clampBarPos(e.x - _dragged_x);
            updateScrollValue();
        }
        else {
            if (_bar.contains(vec2i(e.x, e.y))) {
                _dragged_x = -1;
            }
            else {
                _dragged_x = -2;
            }
        }
    }

    void HorizontalScrollbar::onMouseScrolled(MouseScrollEvent& e)
    {
        _scroll_value = pgt::clamp(_scroll_value + e.scroll, 0, _max_scroll);
        updateBarPos();
    }

    void HorizontalScrollbar::setMaxScroll(int max)
    {
        _max_scroll = _max_scroll = (max > 0) ? max : 0;
        _scroll_value = pgt::clamp(_scroll_value, 0, _max_scroll);
        updateBarPos();
    }

    void HorizontalScrollbar::setBarPercentage(float bar_percentage)
    {
        _bar_percentage = bar_percentage;
        updateBarBounds();
    }

    int HorizontalScrollbar::getValue()
    {
        return _scroll_value;
    }
    void HorizontalScrollbar::setValue(int val)
    {
        _scroll_value = val;
        updateBarPos();
    }
    void HorizontalScrollbar::updateBarBounds()
    {
        Rectangle bnds = getBounds();
        _bar.pos.y = bnds.pos.y + _border_width;
        _bar.size.y = bnds.size.y - _border_width * 2;
        _bar.size.x = _bar_percentage * bnds.size.x;
        updateBarPos();
    }

    void HorizontalScrollbar::updateBarPos()
    {
        _bar.pos.x = getBounds().pos.x + _border_width +
                     (((float)_scroll_value) / _max_scroll) *
                         (getBounds().size.x - _bar.size.x - _border_width * 2);
    }

    void HorizontalScrollbar::updateScrollValue()
    {
        _scroll_value =
            (((float)(_bar.pos.x - getBounds().pos.x - _border_width) /
              (getBounds().size.x - _bar.size.x - _border_width * 2))) *
            _max_scroll;
    }

    int HorizontalScrollbar::clampBarPos(int pos_y)
    {
        return pgt::clamp(pos_y, getBounds().pos.x + _border_width,
                         getBounds().pos.x + getBounds().size.x - _bar.size.x -
                             _border_width);
    }
}
