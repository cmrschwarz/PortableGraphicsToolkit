#pragma once
#include <pgt/window/gui/events/events.h>
#include <pgt/window/gui/GuiComponentContainer.h>
namespace pgt {
    template <class BASE_T, class COMPONENT_T>
    class LayerContainer : public GuiComponentContainer<BASE_T, COMPONENT_T> {
    public:
        using GuiComponentContainer<BASE_T, COMPONENT_T>::GuiComponentContainer;
        typedef LayerContainer<BASE_T, COMPONENT_T> Container_t;
        typedef BASE_T ContainerBase_t;
        typedef COMPONENT_T ContainerComponent_t;
    public:
        void raiseOnMove(MoveEvent& e) override
        {
            ContainerBase_t::raiseOnMove(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnMove, e);
        }
        void raiseOnResize(ResizeEvent& e)
        {
            ContainerBase_t::raiseOnResize(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnResize, e);
        }
    };
}