#pragma once
#include "Layer.h"
namespace pgt {
    // TODO: find a better name for this
    class RenderingLayer : public Layer {
      public:
        virtual void onRender(){};
        virtual void raiseOnRender()
        {
            onRender();
            RenderEvent e;
            callCallback(e);
        }
    };
}