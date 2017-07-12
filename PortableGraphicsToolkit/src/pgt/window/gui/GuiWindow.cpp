#include "GuiWindow.h"

namespace pgt {
    // initialisation order matches declaration order
    GuiWindow::GuiWindow() : GuiWindow(window_creation_hints())
    {
    }

    GuiWindow::GuiWindow(const window_creation_hints& h)
        : Window(h), _layer_2d(*this), _panel(), _gui_layer(_panel)
    {
        init();
        engine::getApp().requestEventBased(true);
    }

    GuiWindow::~GuiWindow()
    {
    }

    bool GuiWindow::prefersEventBased() const
    {
        return true;
    }

    Panel& GuiWindow::getPanel()
    {
        return _panel;
    }


    ParentLayer2D& GuiWindow::getLayer2D()
    {
        return _layer_2d;
    }

    void GuiWindow::internal_update()
    {
        clear();
        raiseOnTick();
        raiseOnRender();
        swapBuffers();
    }

    void GuiWindow::init()
    {
        _layer_2d.addSubLayer(_gui_layer);
        this->addLayer(_layer_2d);
    }
}