#pragma once
#include "Layer2D.h"
#include "LayerContainer.h"
#include "SubLayer2D.h"
namespace pgt {

    class ParentLayer2D : public LayerContainer<Layer2D, SubLayer2D> {
    public:
        using LayerContainer<Layer2D, SubLayer2D>::LayerContainer;
    public:
        // overloading
        void addSubLayer(SubLayer2D& comp)
        {
            Container_t::addComponent(comp);
            ResizeEvent re(
                vec2i(getWindow().getWidth(), getWindow().getHeight()));
            raiseOnResize(re);
        }
        void removeSubLayer(SubLayer2D& l)
        {
            Container_t::removeComponent(l);
        }
        void raiseOnRender() override
        {
            _renderer_2d.begin();
            onRender();
            callCallback((RenderEvent()));
            Render2DEvent re(_renderer_2d);
            raiseOnRender(re);
            _renderer_2d.end();
        }
        void raiseOnRender(Render2DEvent& e) override
        {
            Layer2D::raiseOnRender(e);
            this->forwardEvent(&ContainerComponent_t::raiseOnRender, e);
        }
    };
}