#include "ListView.h"
#include <pgt/graphics/graphics_2d.h>
namespace pgt {

    void ListView::onResize(ResizeEvent& e)
    {
        updateScrollbars();
    }

    void ListView::raiseOnRender(Render2DEvent& e)
    {
        ContainerBase_t::raiseOnRender(e);
        e.renderer.setColor(Color::GRAY);
        e.renderer.fillRectangle(getBounds().pos, getBounds().size);
        e.renderer.pushViewport(getBounds().pos, getBounds().size);
        int it_width;
        if (_item_width != -1) {
            it_width = _item_width;
        }
        else {
            if (_vertical_scrollbar->isVisible()) {
                it_width = getBounds().size.x -
                           _vertical_scrollbar->getBounds().size.x;
            }
            else {
                it_width = getBounds().size.x;
            }
        }
        ListViewItemRenderEvent r(e.renderer, vec2i(it_width, _item_height));
        int imin = _vertical_scrollbar->getValue() / _item_height;
        int imax = imin + getBounds().size.y / _item_height + 1;

        decltype(_components)::iterator end;

        if (imax >= _components.size()) {
            end = _components.end();
        }
        else {
            end = _components.begin() + imax + 1;
        }
        vec2i pos(-_horizontal_scrollbar->getValue(),
                  (imin * _item_height) - _vertical_scrollbar->getValue());

        for (auto it = _components.begin() + imin; it != end; ++it) {
            r.pos = pos;
            (*it)->raiseOnRender(r);
            pos.y += _item_height;
        }
        e.renderer.popViewport();
        _horizontal_scrollbar->raiseOnRender(e);
        _vertical_scrollbar->raiseOnRender(e);
    }

    void ListView::raiseOnMouseButtonDown(MouseButtonDownEvent& e)
    {
        ContainerBase_t::raiseOnMouseButtonDown(e);
        if (_vertical_scrollbar->getBounds().contains(vec2i(e.x, e.y)))
            _vertical_scrollbar->raiseOnMouseButtonDown(e);
        if (_horizontal_scrollbar->getBounds().contains(vec2i(e.x, e.y)))
            _horizontal_scrollbar->raiseOnMouseButtonDown(e);
    }

    void ListView::raiseOnMouseButtonUp(MouseButtonUpEvent& e)
    {
        ContainerBase_t::raiseOnMouseButtonUp(e);
        _vertical_scrollbar->raiseOnMouseButtonUp(e);
        _horizontal_scrollbar->raiseOnMouseButtonUp(e);
    }
    void ListView::raiseOnMouseMoved(MouseMoveEvent& e)
    {
        ContainerBase_t::raiseOnMouseMoved(e);
        _vertical_scrollbar->raiseOnMouseMoved(e);
        _horizontal_scrollbar->raiseOnMouseMoved(e);
    }
    ListView::ListView()
    {
        _horizontal_scrollbar = &pgt::new_mo<HorizontalScrollbar>();
        _vertical_scrollbar = &pgt::new_mo<VerticalScrollbar>();
    }

    ListView::~ListView()
    {
        _horizontal_scrollbar->deleteMe();
        _vertical_scrollbar->deleteMe();
    }

    void ListView::addItem(ListViewItem& it)
    {
        _components.push_back(&it);
        updateScrollbars();
    }

    ListViewItem& ListView::getItem(int index)
    {
        return *_components[index];
    }

    void ListView::setItem(int index, ListViewItem& it)
    {
        _components[index]->deleteMe();
        _components[index] = &it;
    }

    void ListView::removeItem(int index)
    {
        _components[index]->deleteMe();
        _components.erase(_components.begin() + index);
        updateScrollbars();
    }

    void ListView::clear()
    {
        for (ListViewItem* i : _components) {
            i->deleteMe();
        }
        _components.clear();
        updateScrollbars();
    }

    void ListView::setHorizontalScrollbarVisibility(ScrollbarVisibility sbv)
    {
        _horizontal_scrollbar_visibility = sbv;
        updateScrollbars();
    }

    void ListView::setVerticalScrollbarVisibility(ScrollbarVisibility sbv)
    {
        _vertical_scrollbar_visibility = sbv;
        updateScrollbars();
    }

    void ListView::setItemWidth(int width)
    {
        _item_width = width;
    }

    void ListView::setItemWidthDefault()
    {
        _item_width = -1;
    }

    void ListView::updateScrollbars()
    {
        const Rectangle& r = getBounds();
        int height = r.size.y;
        if (_horizontal_scrollbar_visibility == ALWAYS_VISIBLE ||
            (_item_width > getBounds().size.x &&
             _horizontal_scrollbar_visibility != ALWAYS_HIDDEN)) {
            // we need a horizontal scrollbar for sure, no matter if we have
            // vertical
            _horizontal_scrollbar->setVisible(true);
            _horizontal_scrollbar->setBounds(
                Rectangle(r.pos.x, r.pos.y + r.size.y - 22, r.size.x, 22));
            height -= 22;
            _horizontal_scrollbar->setMaxScroll(_item_width -
                                                getBounds().size.x);
            _horizontal_scrollbar->setBarPercentage((float)getBounds().size.x /
                                                    _item_width);
        }
        else {
            _horizontal_scrollbar->setVisible(false);
        }


        if (_vertical_scrollbar_visibility == ALWAYS_HIDDEN ||
            (_vertical_scrollbar_visibility == AS_NEEDED &&
             _item_height * _components.size() <= height)) {
            // sb forced invisible or not needed
            _vertical_scrollbar->setVisible(false);
        }
        else {
            _vertical_scrollbar->setVisible(true);
            _vertical_scrollbar->setMaxScroll(
                _components.size() * _item_height - height);
            _vertical_scrollbar->setBarPercentage(
                (float)height / (_item_height * _components.size()));
            _vertical_scrollbar->setBounds(
                Rectangle(r.pos.x + r.size.x - 22, r.pos.y, 22, r.size.y));
            // we ave a vertical scrollbar. we might need a horizontal one
            // because of that
            int vis_width =
                (getBounds().size.x - _vertical_scrollbar->getBounds().size.x);
            if (_horizontal_scrollbar_visibility != ALWAYS_HIDDEN &&
                _item_width > vis_width) {
                _horizontal_scrollbar->setVisible(true);
                _horizontal_scrollbar->setBounds(Rectangle(
                    r.pos.x, r.pos.y + r.size.y - 22, r.size.x - 22, 22));

                _horizontal_scrollbar->setMaxScroll(_item_width - vis_width);
                _horizontal_scrollbar->setBarPercentage((float)vis_width /
                                                        _item_width);
            }
        }
    }

    void ListView::raiseOnKeyDown(KeyDownEvent& e)
    {
        ContainerBase_t::raiseOnKeyDown(e);
    }
    void ListView::raiseOnMouseScrolled(MouseScrollEvent& e)
    {
        ContainerBase_t::raiseOnMouseScrolled(e);
        _vertical_scrollbar->raiseOnMouseScrolled(e);
    }
}
