#pragma once
#include "Node_legacy.h"
#include "Port.h"
#include <pgt/graphics/graphics_2d.h>

namespace lgs {
    class NAND : public Node_legacy {
    private:
        Port _input1;
        Port _input2;
        Port _output;

    public:
        NAND()
            : _input1(*this, false),
              _input2(*this, false),
              _output(*this, false) {
            setBounds(pgt::Rectangle(20, 20, 50, 50));
        }

        void onRender(pgt::Render2DEvent& e) override {
            e.renderer.setColor(pgt::Color(0xFF333333));
            const pgt::Rectangle& r = getBounds();
            e.renderer.fillRectangle(r.pos, r.size);

            e.renderer.setColor(pgt::Color::YELLOW);
            e.renderer.fillCircle(
                pgt::vec2i(r.pos.x + r.size.x / 2, r.pos.y + r.size.y / 2),
                r.size.y / 3);
            _input1.render(e.renderer);
            _input2.render(e.renderer);
            _output.render(e.renderer);
        }
        bool update() override {
            bool old_val = _output.value;
            _input1.pollState();
            _input2.pollState();
            _output.value = !(_input1.value && _input2.value);
            return (_output.value != old_val);
        }
        Port& getInput1() {
            return _input1;
        }
        Port& getInput2() {
            return _input2;
        }
        Port& getOutput() {
            return _output;
        }
        void relayout() {}
        void onResize(pgt::ResizeEvent& e) {
            _input1.bounds.pos = pgt::vec2i(0, 0);
            _input2.bounds.pos =
                pgt::vec2i(0, getBounds().size.y - _input1.bounds.size.y);
            _output.bounds.pos =
                pgt::vec2i(getBounds().size.x - _output.bounds.size.x,
                          getBounds().size.y / 2 - _output.bounds.size.y / 2);
        }
    };
}