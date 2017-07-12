#include "Connection.h"
#include <pgt/graphics/graphics_2d.h>
#include <pgt/window/gui/Rectangle.h>
#include "Port.h"
#include "Node_legacy.h"
namespace lgs {

    void Connection::render(pgt::Renderer2D& r) {
        pgt::vec2i pos1 =
            p1.node.getBounds().pos + p1.bounds.pos + p1.bounds.size / 2;
        pgt::vec2i pos2 =
            p2.node.getBounds().pos + p2.bounds.pos + p2.bounds.size / 2;
        r.setColor((p1.value || p2.value) ? pgt::Color::BLUE : pgt::Color::BLACK);
        r.drawLine(pos1, pos2, 3);
    }
}
