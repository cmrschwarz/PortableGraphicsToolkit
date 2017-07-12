#pragma once
#include "Node_legacy.h"
#include "Port.h"
#include <pgt/graphics/graphics_2d.h>

namespace lgs {
    class Button : public Node_legacy {
    private:
        Port _port;
        bool _value;


    public:
        Button::Button() : _port(*this, false), _value(false) {
            setBounds(pgt::Rectangle(20, 20, 50, 50));
        }
        void onMouseButtonDown(pgt::MouseButtonDownEvent& e) override {
            Node_legacy::onMouseButtonDown(e);
            _value = !_value;
            _port.value = _value;
        }
        void onRender(pgt::Render2DEvent& e) override {
            e.renderer.setColor(_value ? pgt::Color::GREEN : pgt::Color::RED);
            const pgt::Rectangle& r = getBounds();
            e.renderer.fillRectangle(r.pos, r.size);
        }
        bool update() override {
            return false;
        }
        Port& getPort() {
            return _port;
        }
    };
}