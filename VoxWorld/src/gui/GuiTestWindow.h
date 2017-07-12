#pragma once
#include <pgt/window/gui/GuiWindow.h>
#include <pgt/graphics/graphics_2d_fwd.h>
namespace gui {
    class GuiTestWindow : public pgt::GuiWindow {
    public:
        GuiTestWindow();
        ~GuiTestWindow();
        void onKeyDown(pgt::KeyDownEvent& e) override;

    private:
        static pgt::window_creation_hints getHints();
        pgt::Renderer2D* _renderer;
    };
}  // namespace gui
