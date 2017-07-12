#pragma once
#include <pgt/window/gui/controls/RectangularControl.h>
#include <pgt/window/layers/SubLayer2D.h>
namespace pgt {
    class GuiLayer : public SubLayer2D {
    private:
        RectangularControl& _control;

    public:
        GuiLayer(RectangularControl& rectangular_control)
            : _control(rectangular_control)
        {
        }
        ~GuiLayer()
        {
            _control.deleteMe();
        }

    public:
        void raiseOnRender(Render2DEvent& e) override
        {
            SubLayer2D::raiseOnRender(e);
            _control.raiseOnRender(e);
        }
        void raiseOnResize(ResizeEvent& e) override
        {
            SubLayer2D::raiseOnResize(e);
            _control.setBounds(Rectangle(0, 0, e.size_new.x, e.size_new.y));
            // not forwarded to panel
        }
        void raiseOnMove(MoveEvent& e) override
        {
            SubLayer2D::raiseOnMove(e);
            // not forwarded to panel
        }
        void raiseOnTick() override
        {
            SubLayer2D::raiseOnTick();
            _control.raiseOnTick();
        }
        void raiseOnFocusGained() override
        {
            SubLayer2D::raiseOnFocusGained();
            _control.raiseOnFocusGained();
        }
        void raiseOnFocusLost() override
        {
            SubLayer2D::raiseOnFocusLost();
            _control.raiseOnFocusLost();
        }
        void raiseOnKeyDown(KeyDownEvent& e) override
        {
            SubLayer2D::raiseOnKeyDown(e);
            _control.raiseOnKeyDown(e);
        }
        void raiseOnKeyUp(KeyUpEvent& e) override
        {
            SubLayer2D::raiseOnKeyUp(e);
            _control.raiseOnKeyUp(e);
        }
        void raiseOnMouseButtonDown(MouseButtonDownEvent& e) override
        {
            SubLayer2D::raiseOnMouseButtonDown(e);
            _control.raiseOnMouseButtonDown(e);
        }
        void raiseOnMouseButtonUp(MouseButtonUpEvent& e) override
        {
            SubLayer2D::raiseOnMouseButtonUp(e);
            _control.raiseOnMouseButtonUp(e);
        }
        void raiseOnMouseMoved(MouseMoveEvent& e) override
        {
            SubLayer2D::raiseOnMouseMoved(e);
            _control.raiseOnMouseMoved(e);
        }
        void raiseOnMouseScrolled(MouseScrollEvent& e) override
        {
            SubLayer2D::raiseOnMouseScrolled(e);
            _control.raiseOnMouseScrolled(e);
        }
    };
}