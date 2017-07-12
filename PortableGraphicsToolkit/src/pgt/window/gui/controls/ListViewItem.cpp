#include "ListViewItem.h"
#include <pgt/graphics/Graphics_2d.h>
namespace pgt {

    ListViewItem::ListViewItem()
    {
        _color = Color::randomColor();
    }

    void ListViewItem::raiseOnRender(ListViewItemRenderEvent& e)
    {
        onRender(e);
        callCallback(e);
    }

    void ListViewItem::onRender(ListViewItemRenderEvent& e)
    {
        e.renderer.setColor(_color);
        e.renderer.fillRectangle(e.pos, e.size);
        e.renderer.setColor(Color::GREEN);
        e.renderer.fillCircle(e.pos + vec2i(20, 16), 7);
        e.renderer.fillRectangle(e.pos + vec2i(e.size.x - 10, 0),
                                 vec2i(10, e.size.y));
    }
}
