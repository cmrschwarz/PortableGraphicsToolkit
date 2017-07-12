#include <stdio.h>
#include <pgt/window/window.h>
#include <pgt/window/gui/gui.h>
#include "Scene.h"
#include <pgt/window/gui/GuiLayer.h>
#include <pgt/window/layers/ParentLayer2D.h>
#include <pgt/utils/debug/MessageBoxes.h>
#include <pgt/io/filesystem/FileSystem.h>
#include <pgt/io/istreams/istreams.h>
#undef main
bool scmp(const char* a, const char* b, size_t len) {
    const char* aend = a + len;
    while (a != aend) {
        if (*a != *b) return false;
        a++;
        b++;
    }
    return true;
}
void handleFolder(std::string path) {
    std::vector<std::string> _sub_folders =
        pgt::FileSystem::getAllFoldersWithinFolder(path);
    std::vector<std::string> _files =
        pgt::FileSystem::getAllFilesWithinFolder(path);
    for (std::string& fi : _files) {
        std::string f(fi);
        for (auto it = f.begin(); it != f.end(); ++it) {
            const char* sp = &*it;
            if (scmp(sp, u8"�", 2)) f.replace(it, it + 2, "ae");
            if (scmp(sp, u8"�", 2)) f.replace(it, it + 2, "Ae");
            if (scmp(sp, u8"�", 2)) f.replace(it, it + 2, "oe");
            if (scmp(sp, u8"�", 2)) f.replace(it, it + 2, "Oe");
            if (scmp(sp, u8"�", 2)) f.replace(it, it + 2, "ue");
            if (scmp(sp, u8"�", 2)) f.replace(it, it + 2, "Ue");
        }
        if (f != fi) {
            pgt::FileSystem::renameFile(path + '/' + fi, f);
        }
    }
    for (std::string& s : _sub_folders) {
        handleFolder(path + "/" + s);
    }
}
int main() {
    // std::string path = "C:/Users/Christian/Desktop/t";
    //  handleFolder(w, path, 0);
    pgt::engine::initApp();
    pgt::window_creation_hints h;
    h.tps = 60;
    h.vSync = true;
    pgt::GuiWindow win(h);
    win.getLayer2D().addSubLayer(
        pgt::new_mo<pgt::GuiLayer>(pgt::new_mo<lgs::Scene>()));
    win.setMinimumSize(pgt::vec2i(640, 480));
    pgt::engine::getApp().run();
}
