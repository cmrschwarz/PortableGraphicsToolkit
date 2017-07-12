#pragma once
#include "Node_legacy.h"
#include "Port.h"
#include <pgt/graphics/graphics_2d.h>

namespace lgs {
    class LED : public Node_legacy {
    private:
        Port _port;

    public:
        LED() : _port(*this, 0) {
            setBounds(pgt::Rectangle(20, 20, 50, 50));
        }

        void onRender(pgt::Render2DEvent& e) override {
            e.renderer.setColor(_port.value ? pgt::Color::YELLOW
                                            : pgt::Color::DARK_GRAY);
            const pgt::Rectangle& r = getBounds();
            e.renderer.fillRectangle(r.pos, r.size);
        }
        bool update() override {
            bool old_val = _port.value;
            _port.pollState();
            return (_port.value != old_val);
        }
        Port& getPort() {
            return _port;
        }
    };
}