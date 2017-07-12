#pragma once
#include "DraggableControl.h"
#include <pgt/graphics/graphics_2d.h>
namespace pgt {
    class DraggableButton : public DraggableControl {
    public:
        Font t;
        DraggableButton()
            : t("ArialRoundedMt", 20,
                pgt::VfsFileStreamReader("res/fonts/arialroundedmt.ttf"))
        {
            setBounds(Rectangle(0, 0, 50, 50));
        }
        bool isInBounds(const vec2i& p) const override
        {
            return getBounds().contains(p);
        }
        void onRender(Render2DEvent& e) override
        {
            e.renderer.setColor(pgt::Color::YELLOW);
            e.renderer.fillRectangle(getBounds().pos, getBounds().size);
            e.renderer.setColor(pgt::Color::BLACK);
            e.renderer.setFont(t);
            e.renderer.drawString("DB", getBounds().pos);
        }
    };
}