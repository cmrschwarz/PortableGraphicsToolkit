#pragma once
#include <pgt/window/gui/GuiComponent2DContainer.h>
namespace pgt {
    template <class BASE_T, class COMPONENT_T>
    class ControlContainer
        : public GuiComponent2DContainer<BASE_T, COMPONENT_T> {
    public:
        typedef ControlContainer<BASE_T, COMPONENT_T> Container_t;
        using GuiComponent2DContainer<BASE_T,
                                      COMPONENT_T>::GuiComponent2DContainer;
    };
}