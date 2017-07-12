#pragma once
#include "GuiComponentContainer.h"
namespace pgt {
    template <class BASE_T, class COMPONENT_T>
    class GuiComponent2DContainer
        : public GuiComponentContainer<BASE_T, COMPONENT_T> {
    public:
        typedef GuiComponent2DContainer<BASE_T, COMPONENT_T> Container_t;
        typedef BASE_T ContainerBase_t;
        typedef COMPONENT_T ContainerComponent_t;


        void raiseOnRender(Render2DEvent& e)
        {
            ContainerBase_t::raiseOnRender(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnRender, e);
        }
    };
}