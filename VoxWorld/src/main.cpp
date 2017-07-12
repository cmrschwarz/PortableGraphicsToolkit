#include <pgt/window/plattform/glfw/GlfwManager.h>
#include <pgt/window/window.h>
#include "gui/GuiTestWindow.h"
#include <pgt/io/logger/logger.h>
#include <game/VoxelTest.h>
#include <pgt/utils/debug/MessageBoxes.h>
// For Real Release set /ENTRY:"mainCRTStartup"  and SubSystemConsole in Linker
void eventCallback(pgt::Event& e);

void gameTest() {
    pgt::engine::initApp();
    //   auto win = game::VoxelTest(); //TODO: investigate
    game::VoxelTest win;
    pgt::engine::getApp().run();
}
void guiTest() {
    pgt::engine::initApp();
    gui::GuiTestWindow win;
    pgt::engine::getApp().run();
}

void multiWindowTest() {
    pgt::engine::initApp();
    gui::GuiTestWindow win;
    game::VoxelTest win2;
    pgt::engine::getApp().run();
}
void minimalTest() {
    pgt::engine::initApp();
    pgt::Window win{pgt::window_creation_hints()};
    pgt::engine::getApp().run();
}
void simpleTest() {
    pgt::engine::initApp();
    auto& win = pgt::new_mo<pgt::GuiWindow>(pgt::window_creation_hints());
    win.getPanel().setCallback(eventCallback);
    pgt::engine::getApp().run();
    pgt::engine::terminateApp();
}
void threadTest() {
    for (int i = 0; i < 5; i++) {
        std::thread* t = new std::thread([]() { simpleTest(); });
        t->detach();
    }
    guiTest();
}
void leakTest() {
    for (int i = 0; i < 4; i++) {
        simpleTest();
    }
}
void eventCallback(pgt::Event& e) {
    if (e.is<pgt::Render2DEvent>()) {
        auto& rndr = e.cast<pgt::Render2DEvent>().renderer;
        auto& win = pgt::engine::getWindowCurrent();
        rndr.setColor(pgt::Color::BLUE);
        rndr.fillRectangle(pgt::vec2i(0, 0),
                           pgt::vec2i(win.getWidth(), win.getHeight()));
        rndr.setColor(pgt::Color::RED);
        rndr.drawLine(pgt::vec2i(50, 50), pgt::vec2i(400, 400), 5);
        rndr.setColor(pgt::Color::randomColor());
        rndr.fillCircle(pgt::vec2i(300, 300), 50);
    }
    if (e.is<pgt::KeyDownEvent>()) {
        auto& ec = e.cast<pgt::KeyDownEvent>();
        if (ec.key == pgt::KEY_ESCAPE) {
            ((pgt::GuiWindow&)pgt::engine::getWindowCurrent())
                .getPanel()
                .clearCallback();
            pgt::engine::getWindowCurrent().close();
            pgt::window_creation_hints wch;
            wch.title = "new window";
            auto& w = pgt::new_mo<pgt::GuiWindow>(wch);
            w.getPanel().setCallback(eventCallback);
        }
        // leak test
        if (ec.key == pgt::KEY_F8) {
            pgt::engine::getWindowCurrent().close();
            pgt::window_creation_hints wch;
            wch.title = "new window";
            auto& w = pgt::new_mo<pgt::GuiWindow>(wch);
            w.getPanel().setCallback(eventCallback);
        }
        if (ec.key == pgt::KEY_F9) {
            std::thread* t = new std::thread([]() { simpleTest(); });
            t->detach();
        }
    }
}

#undef main
int main() {
	PGT_LOG_INFO("24");
    gameTest();
    return 0;
}
