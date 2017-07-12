#pragma once
#include <pgt/window/window.h>
#include <pgt/window/layers/RenderingLayer.h>
#include <pgt/graphics/graphics_2d.h>

#include "LayerContainer.h"
namespace pgt {

    class Layer2D : public RenderingLayer {
    private:
    protected:
        Renderer2D _renderer_2d;
        Window& _window;

    public:
        virtual void raiseOnRender()
        {
            _renderer_2d.begin();
            onRender();
            callCallback((RenderEvent()));
            Render2DEvent re(_renderer_2d);
            raiseOnRender(re);
            _renderer_2d.end();
        }
        // so it doesn't complain...
        virtual void onRender() override
        {
            RenderingLayer::onRender();
        };
        virtual void raiseOnRender(Render2DEvent& e)
        {
            onRender(e);
            callCallback(e);
        }
        virtual void onRender(Render2DEvent& e){};

    public:
        Layer2D(Window& win) : _window(win), _renderer_2d()
        {
        }
        ~Layer2D()
        {
        }
        Renderer2D& getRenderer2D()
        {
            return _renderer_2d;
        }
        Window& getWindow()
        {
            return _window;
        }
    };
}