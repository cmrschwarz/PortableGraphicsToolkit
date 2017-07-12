#include "Port.h"
#include "Node_legacy.h"
namespace lgs {


    void Port::render(pgt::Renderer2D& r) {
        if (value) {
            r.setColor(pgt::Color::BLUE);
        }
        else {
            r.setColor(pgt::Color::BLACK);
        }
        r.fillRectangle(node.getBounds().pos + bounds.pos, bounds.size);
    }

    void Port::pollState() {
        for (auto it = connections.begin(); it != connections.end(); ++it) {
            if ((*it)->value == true) {
                value = true;
                return;
            }
        }
        value = false;
    }
}
