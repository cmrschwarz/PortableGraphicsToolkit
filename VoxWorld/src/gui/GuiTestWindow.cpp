#include "GuiTestWindow.h"
#include <pgt/window/gui/controls/button.h>
#include <pgt/graphics/plattform/opengl/GlFramebuffer.h>
#include <pgt/utils/debug/MessageBoxes.h>
#include <pgt/graphics/Image/Image.h>
#include <pgt/graphics/plattform/opengl/GlTexture.h>
#include <pgt/graphics/image/ImageRGBA.h>
#include <pgt/graphics/plattform/software/SwRenderer.h>
#include <pgt/io/filesystem/FileSystem.h>
#include <pgt/window/gui/controls/DraggableButton.h>
bool grrnToYellow = false;
bool lineToOrange = false;
std::string _text = "Hello, World!";
namespace gui {
    GuiTestWindow::GuiTestWindow() : pgt::GuiWindow(getHints()) {
        decltype(*this)& self = *this;
        pgt::Button* b = &pgt::new_mo<pgt::Button>();  // MEH works like a charm :)
        pgt::DraggableButton* db = &pgt::new_mo<pgt::DraggableButton>();
        b->setBounds(pgt::Rectangle(20, 350, 60, 24));
        b->setBackColor(pgt::Color::BLACK);
        b->setCallback([b](pgt::Event& e) {
            if (e.is<pgt::MouseButtonDownEvent>()) {
                auto& mc = (pgt::MouseButtonDownEvent&)e;
                if (mc.button != pgt::MBUTTON_LEFT) return;
                pgt::Color n = pgt::Color::BLACK;
                if (b->getBackColor() == pgt::Color::BLACK) {
                    n = pgt::Color::YELLOW;
                }
                b->setBackColor(n);
            }
        });
        pgt::Panel& p = getPanel();
        p.addControl(*b);
        p.addControl(*db);
        unsigned const char a = 'A';


        auto* font = new pgt::Font(
            "", 150, pgt::VfsFileStreamReader("res/fonts/arialroundedmt.ttf"));
        pgt::Image img1(pgt::FileStreamReader("res/images/Test0.png"));
        auto* my_canvas = new pgt::ImageRGBA(20, 20);
        auto* swrenderer = new pgt::SwRenderer<pgt::ImageRGBA>(*my_canvas);
        pgt::Image img2(pgt::FileStreamReader("res/images/Test2.png"));
        pgt::Image img3(pgt::FileStreamReader("res/images/Test3.png"));

        pgt::Texture* my_tex3 = new pgt::Texture(img2);
        pgt::Texture* my_tex2 = new pgt::Texture(img3);
        pgt::Texture* my_tex = new pgt::Texture(*my_canvas);
        getPanel().setCallback([=, &p](pgt::Event& e) {
            if (e.is<pgt::Render2DEvent>()) {
                swrenderer->setColor(pgt::Color::WHITE);
                swrenderer->fillRectangle(
                    pgt::vec2i(0, 0),
                    pgt::vec2i(my_canvas->getWidth(), my_canvas->getHeight()));
                swrenderer->setColor(pgt::Color::RED);
                swrenderer->fillTriangle(pgt::vec2i(0, 19), pgt::vec2i(19, 19),
                                         pgt::vec2i(10, 0));
                my_tex->setImage(*my_canvas);
                auto& re = e.cast<pgt::Render2DEvent>();
                re.renderer.end();
                re.renderer.begin();

                re.renderer.setColor(pgt::Color::DARK_GRAY);
                re.renderer.fillRectangle(p.getBounds().pos,
                                          p.getBounds().size);
                re.renderer.pushViewport(pgt::vec2i(600, 5),
                                         pgt::vec2i(300, 300));
                for (size_t x = 0; x < 300; x += 12) {
                    for (size_t y = 0; y < 300; y += 12) {
                        re.renderer.setColor(pgt::Color::randomColor());
                        re.renderer.fillCircle(pgt::vec2i(x, y), 5);
                    }
                }
                re.renderer.popViewport();

                re.renderer.drawTexture(*my_tex2, pgt::vec2i(200, 0),
                                        pgt::vec2i(200, 200));
                re.renderer.drawTexture(*my_tex3, pgt::vec2i(400, 0),
                                        pgt::vec2i(200, 200));
                re.renderer.setColor(pgt::Color::GREEN);
                re.renderer.fillCircle(pgt::vec2i(400, 400), 90);

                re.renderer.setColor(pgt::Color::BLUE);
                re.renderer.fillTriangle(pgt::vec2i(250, 50),
                                         pgt::vec2i(430, 100),
                                         pgt::vec2i(400, 70));
                re.renderer.setColor(pgt::Color::RED);
                re.renderer.fillQuad(pgt::vec2i(40, 555), pgt::vec2i(700, 450),
                                     pgt::vec2i(700, 580), pgt::vec2i(20, 580));
                re.renderer.drawTexture(*my_tex, pgt::vec2i(0, 0),
                                        pgt::vec2i(200, 200));

                re.renderer.setFont(*font);
                pgt::vec3i tex_siz = re.renderer.getFont().measureString(_text);
                re.renderer.setColor(pgt::Color::BLACK);
                re.renderer.fillRectangle(
                    pgt::vec2i(150, 600 + tex_siz.z),
                    pgt::vec2i(tex_siz.x, tex_siz.y - tex_siz.z));
                re.renderer.setColor(pgt::Color::GREEN);

                re.renderer.drawString(_text, pgt::vec2i(150, 600));
            }
            if (e.is<pgt::KeyDownEvent>()) {
                auto& ke = e.cast<pgt::KeyDownEvent>();
                if (ke.key == pgt::KEY_SHIFT_L) return;
                if (ke.key == pgt::KEY_BACKSPACE) {
                    _text.pop_back();
                    return;
                }
                char c = ke.key;
                if (!ke.shift) {
                    if (c >= 'A' && c <= 'Z') c += 32;
                }
                _text += (char)c;
            }
        });
    }
    GuiTestWindow::~GuiTestWindow() {}


    void GuiTestWindow::onKeyDown(pgt::KeyDownEvent& ke) {
        if (true && ke.key == pgt::KEY_F1) {
            setFullscreen(!isFullscreen());
        }
        if (ke.key == pgt::KEY_ESCAPE) {
            pgt::engine::terminateApp();
        }
        if (ke.key == pgt::KEY_F12) {
            new GuiTestWindow();
            pgt::engine::getApp().setRenderingContext(getRenderingContext());
        }
    }

    pgt::window_creation_hints GuiTestWindow::getHints() {
        pgt::window_creation_hints h;
        h.fullscreen = false;
        h.vSync = true;
        return h;
    }
}  // namespace gui
