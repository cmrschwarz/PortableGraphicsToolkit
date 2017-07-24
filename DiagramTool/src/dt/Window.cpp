#include "Window.h"
#include <pgt/graphics/plattform/opengl/GlFramebuffer.h>
#include <pgt/graphics/image/ImageRGBA.h>
#include <pgt/io/istreams/istreams.h>
#include <pgt/graphics/plattform/opengl/GlTexture.h>
#include <pgt/io/filesystem/Filesystem.h>

namespace dt {

    Window::~Window()
    {
        int i = 0;
    }

    Window::Window(dt::Table& t) : pgt::GuiWindow(getHints()), _diagram(*this, t)
    {
        init();
    }

    void Window::setClickCallback(CallbackFun fun)
    {
        _diagram.setCallback(fun);
    }

    pgt::window_creation_hints Window::getHints()
    {
        pgt::window_creation_hints hints;
        hints.vSync = true;
        hints.resizable = true;
        hints.title = "Diagram Tool";
        hints.tps = 10;
        hints.width = 640;
        hints.height = 480;
        return hints;
    }


    std::string Window::getAvailableImageName()
    {
        std::string path = pgt::FileSystem::getDesktopPath();
        auto files = pgt::FileSystem::getAllFilesWithinFolder(path);
        std::string name = "Diagram_";
        size_t index = 1;
        std::string attempt;
        bool taken = false;
        while (true) {
            attempt = name + std::to_string(index) + ".png";
            for (auto it = files.begin(); it != files.end(); ++it) {
                if ((*it) == attempt) {
                    taken = true;
                    break;
                }
            }
            if (taken == false) break;
            index++;
            taken = false;
        }
        return path + "/" + attempt;
    }

    void Window::init()
    {
        getPanel().setCallback([&](pgt::Event& e) {

            if (e.is<pgt::Render2DEvent>()) {
                _diagram.onRenderEvent(e.cast<pgt::Render2DEvent>().renderer);
            }
            else if (e.is<pgt::MouseButtonDownEvent>()) {
                _diagram.onClickEvent(e.cast<pgt::MouseButtonDownEvent>());
            }
            else if (e.is<pgt::WindowCloseEvent>()) {
            }
            else if (e.is<pgt::KeyDownEvent>()) {
                auto& ke = e.cast<pgt::KeyDownEvent>();
                if (ke.key == pgt::KEY_F1) {
                    auto& rndr = this->getLayer2D().getRenderer2D();
                    pgt::Texture tex(getWidth(), getHeight());
                    pgt::Framebuffer f(tex.getWidth(), tex.getHeight(), true,
                                      false, &tex, nullptr);
                    pgt::engine::getApp().getRenderingContext().setFramebuffer(
                        f);
                    rndr.begin();
                    _diagram.onRenderEvent(rndr);
                    rndr.end();
                    pgt::engine::getApp()
                        .getRenderingContext()
                        .setDefaultFramebuffer();
                    pgt::Image img(tex);
                    img.saveImage(
                        pgt::FileStreamWriter(getAvailableImageName()));
                    printf("Heureka! \n");
                }
            }
        });
    }
}  // namespace dt
