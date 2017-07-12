#pragma once
#include <pgt/window/window.h>
#include <pgt/window/gui/controls/Panel.h>
#include <pgt/window/layers/ParentLayer2D.h>
#include <pgt/window/gui/GuiLayer.h>
namespace pgt {
    class GuiWindow : public Window {
    private:
        ParentLayer2D _layer_2d;
        Panel _panel;
        GuiLayer _gui_layer;

    public:
        GuiWindow();
        GuiWindow(const window_creation_hints& h);
        ~GuiWindow();

    public:
        bool prefersEventBased() const override;
        Panel& getPanel();

        ParentLayer2D& getLayer2D();
        void internal_update() override;

    private:
        void init();
    };
}