#pragma once
#include "EventComponentContainer.h"
namespace pgt {
    template <class BASE_T, class COMPONENT_T>
    class GuiComponentContainer
        : public EventComponentContainer<BASE_T, COMPONENT_T> {
    public:
        // overloading EventComponentContainer
        typedef GuiComponentContainer<BASE_T, COMPONENT_T> Container_t;
        using EventComponentContainer<BASE_T,
                                      COMPONENT_T>::EventComponentContainer;
        typedef COMPONENT_T ContainerComponent_t;
        typedef BASE_T ContainerBase_t;

    public:
        void raiseOnMouseMoved(MouseMoveEvent& e) override
        {
            ContainerBase_t::raiseOnMouseMoved(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnMouseMoved, e);
        };
        void raiseOnMouseButtonDown(MouseButtonDownEvent& e) override
        {
            ContainerBase_t::raiseOnMouseButtonDown(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnMouseButtonDown, e);
        };
        void raiseOnMouseButtonUp(MouseButtonUpEvent& e) override
        {
            ContainerBase_t::raiseOnMouseButtonUp(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnMouseButtonUp, e);
        };
        void raiseOnMouseScrolled(MouseScrollEvent& e) override
        {
            ContainerBase_t::raiseOnMouseScrolled(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnMouseScrolled, e);
        }
        void raiseOnKeyDown(KeyDownEvent& e) override
        {
            ContainerBase_t::raiseOnKeyDown(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnKeyDown, e);
        };
        void raiseOnKeyUp(KeyUpEvent& e) override
        {
            ContainerBase_t::raiseOnKeyUp(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnKeyUp, e);
        };
        void raiseOnTick() override
        {
            ContainerBase_t::raiseOnTick();
            this->forwardEvent(&ContainerComponent_t::raiseOnTick);
        };
        void raiseOnFocusGained() override
        {
            ContainerBase_t::raiseOnFocusGained();
            this->forwardEvent(&ContainerComponent_t::raiseOnFocusGained);
        };
        void raiseOnFocusLost() override
        {
            ContainerBase_t::raiseOnFocusLost();
            this->forwardEvent(&ContainerComponent_t::raiseOnFocusLost);
        };
    };
}