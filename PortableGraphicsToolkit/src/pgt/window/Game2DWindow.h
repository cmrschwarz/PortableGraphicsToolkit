#pragma once
#include "GameWindow.h"
#include <pgt/graphics/graphics_2d.h>
namespace pgt {
    class Game2DWindow : public GameWindow {
      private:
        Renderer2D _renderer;

      public:
        Game2DWindow(const window_creation_hints& h)
            : GameWindow(h), _renderer()
        {
        }
        virtual void onRender(Render2DEvent& e){};
        virtual void raiseOnRender(Render2DEvent& e)
        {
            onRender(e);
            callCallback(e);
        };
        virtual void raiseOnRender() override
        {
            GameWindow::raiseOnRender();
            _renderer.begin();
            Render2DEvent r2de(_renderer);
            raiseOnRender(r2de);
            _renderer.end();
        }
        Renderer2D& getRenderer2D()
        {
            return _renderer;
        }
    };
}