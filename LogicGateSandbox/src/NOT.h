#pragma once
#include "Node_legacy.h"
#include "Port.h"
#include <pgt/graphics/graphics_2d.h>

namespace lgs {
    class NOT : public Node_legacy {
    private:
        Port _input1;
        Port _output;

    public:
        NOT() : _input1(*this, false), _output(*this, false) {
            setBounds(pgt::Rectangle(20, 20, 50, 50));
        }

        void onRender(pgt::Render2DEvent& e) override {
            e.renderer.setColor(pgt::Color(0xFF333333));
            const pgt::Rectangle& r = getBounds();
            e.renderer.fillRectangle(r.pos, r.size);

            e.renderer.setColor(pgt::Color::RED);
            e.renderer.fillCircle(
                pgt::vec2i(r.pos.x + r.size.x / 2, r.pos.y + r.size.y / 2),
                r.size.y / 3);
            _input1.render(e.renderer);
            _output.render(e.renderer);
        }
        void onResize(pgt::ResizeEvent& e) {
            _input1.bounds.pos =
                pgt::vec2i(0, (getBounds().size.y - _input1.bounds.size.y) / 2);
            _output.bounds.pos =
                pgt::vec2i(getBounds().size.x - _output.bounds.size.y,
                          (getBounds().size.y - _input1.bounds.size.y) / 2);
        }
        bool update() override {
            bool old_val = _output.value;
            _input1.pollState();
            if (!_input1.value) {
                _output.value = true;
            }
            else {
                _output.pollState();
            }
            return (old_val != _output.value);
        }
        Port& getInput1() {
            return _input1;
        }
        Port& getOutput() {
            return _output;
        }
    };
}