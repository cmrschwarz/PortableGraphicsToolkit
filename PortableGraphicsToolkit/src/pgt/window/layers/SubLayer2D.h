#pragma once
#include "Layer.h"
namespace pgt {
    class SubLayer2D : public Layer {
    public:
        SubLayer2D(){}
    public:
        virtual void onRender(Render2DEvent& e){};
        virtual void raiseOnRender(Render2DEvent& e)
        {
            onRender(e);
            callCallback(e);
        }
    };
}