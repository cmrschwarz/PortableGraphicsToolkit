#pragma once
#include <pgt/window/window.h>
#include <pgt/graphics/plattform/opengl/GlShader.h>
#include <pgt/utils\Stopwatch.h>
#include <pgt/graphics/graphics_2d.h>
namespace game {
    class VoxelTest : public pgt::GameWindow {
    private:
        bool _rainbow = false;
        bool _wireframe = false;
        bool _collision = true;
        int l, h;
        pgt::Font _font;
        pgt::Renderer2D _rndr_2d;

        // DONT REORDER THE FOLLOWING OR THE INITIALIZER WILL BREAK
        pgt::Texture _tex;
        pgt::Framebuffer _frmb;


    public:
        VoxelTest();
        ~VoxelTest();

    private:
        void init();
        void onKeyDown(pgt::KeyDownEvent& e) override;
        void onTick() override;
        void onRender() override;
        static pgt::window_creation_hints makeHints();
    };
}  // namespace game