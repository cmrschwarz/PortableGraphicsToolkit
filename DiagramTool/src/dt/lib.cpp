#pragma once
#include "DTDEFS.h"
#include <stdint.h>
#include "Table.h"
#include <string.h>
#include <pgt/window/window.h>
#include "Window.h"
#include <thread>
#include <chrono>
#include <pgt/io/filesystem/FileSystem.h>
#include <pgt/managed_object.h>
CallbackFun _callback = nullptr;
dt::Table _table;
dt::Window* _window = nullptr;
pgt::IApp* _app_evil_handle;
DT_DLL_EXPORT(void) dtSetTableValueStr(uint32_t x, uint32_t y, str_t str)
{
    _table.setValue(x, y, std::string(str, strlen(str)));
}
DT_DLL_EXPORT(void) dtSetTableValueDbl(uint32_t x, uint32_t y, double dbl)
{
    _table.setValue(x, y, dbl);
}
DT_DLL_EXPORT(void) dtShowWindow()
{
    std::thread thr([&]() {
        pgt::engine::initApp();
        _app_evil_handle = &pgt::engine::getApp();
        _window = &pgt::new_mo<dt::Window>(_table);
        _window->setClickCallback(_callback);
        pgt::engine::getApp().run();
        _app_evil_handle = nullptr;
    });
#if PGT_DEBUG
    thr.join();
#else
    thr.detach();
#endif
}
DT_DLL_EXPORT(void) dtReset()
{
    if (_app_evil_handle) {
        _app_evil_handle->terminate();
        while (_app_evil_handle) {
            std::this_thread::yield();
        }
    }
    _table = dt::Table();
}
DT_DLL_EXPORT(void) dtSetClickCallback(CallbackFun callback)
{
    _callback = callback;
    if (_window != nullptr) {
        _window->setClickCallback(_callback);
    }
}
DT_DLL_EXPORT(void) dtSetColumnLineMode(uint32_t c)
{
    _table.getYAxis(c - 1).setDisplayType(dt::DisplayType::LINE);
}
DT_DLL_EXPORT(void)
dtSetColumnColor(uint32_t c, uint32_t r, uint32_t g, uint32_t b)
{
    _table.getYAxis(c - 1).setColor(pgt::Color(r, g, b));
}
void test()
{
    dtSetTableValueStr(0, 0, "X Row Name");
    for (int i = 1; i < 5; i++) {
        dtSetTableValueStr(i, 0, pgt::makeStr("Y Row %i", i).c_str());
    }
    for (int i = 1; i < 20; i++) {
        dtSetTableValueStr(0, i, pgt::makeStr("X Val %i", i).c_str());
    }
    for (int r = 1; r < 5; r++) {
        for (int i = 1; i < 20; i++) {
            dtSetTableValueDbl(r, i, std::rand() % 1000);
        }
    }
    dtSetColumnColor(1, 255, 0, 0);
    dtSetColumnColor(2, 0, 255, 0);
    dtSetColumnColor(3, 0, 0, 255);
    dtSetColumnColor(4, 255, 255, 0);
    dtSetColumnLineMode(2);
    dtSetColumnLineMode(1);
    dtShowWindow();
}
DT_DLL_EXPORT(char) dtGetStr(const char* c, uint32_t offset)
{
    return c[offset];
}
//
void t2(str_t s1, str_t s2, str_t s3, double d)
{
	PGT_LOG_DEBUG("x axis: \"%s\" |  x value: \"%s\"  | y axis: \"%s\"  | y value: %f", s1, s2, s3, d);
}
void leakTest()
{
    dtSetClickCallback(t2);
    for (int i = 0; i < 5; i++) {
        test();
    }
}

// FOR DLL RELEASE ADD "$(ProjectDir)\dll\DLL_EXPORT.def" to
// module definition file in the linker settings [linker/input]
int main()
{
    dtSetClickCallback(t2);
	test();
}