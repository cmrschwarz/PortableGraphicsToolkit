#pragma once
#include <pgt/window/gui/controls/ListViewItem.h>
#include <pgt/graphics/graphics_2d.h>
#include <pgt/window/window.h>
namespace lgs {

    class GateListViewItem : public pgt::ListViewItem {
    private:
        std::string _text;

    public:
        virtual void onRender(pgt::ListViewItemRenderEvent& e) override;
    };

    void GateListViewItem::onRender(pgt::ListViewItemRenderEvent& e) {
        e.renderer.setColor(pgt::Color::LIGHT_GRAY);
        e.renderer.fillRectangle(e.pos, e.size);
        e.renderer.setFont(pgt::engine::getRenderingContextCurrent()
                               .getFontManager()
                               .getDefaultFont());
        e.renderer.setColor(pgt::Color::BLACK);
        e.renderer.drawString("Test", e.pos);
    }
}