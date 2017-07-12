#pragma once
#include "PGTEngine_Glfw.h"
#include <GL/glew.h>
#include <pgt/io/logger/logger.h>
#include "GlfwManager.h"
#include <FreeImage/FreeImage.h>
#include <pgt/io/vfs/VFS.h>
#include <pgt/io/vfs/OSDirectory.h>
#include <pgt/graphics/plattform/opengl/res/Resources.h>
#include <pgt/utils/debug/MessageBoxes.h>
namespace pgt {
    decltype(PGTEngine_Glfw::_windows) PGTEngine_Glfw::_windows;
    decltype(
        PGTEngine_Glfw::_rendering_context) PGTEngine_Glfw::_rendering_context;
    bool PGTEngine_Glfw::_initialized;
    bool PGTEngine_Glfw::_running;

    void PGTEngine_Glfw::init()
    {
        _initialized = true;
        PGT_LOG_INFO("Initialized PGTEngine_Glfw");
        const char* gl_version =
            reinterpret_cast<const char*>(glGetString(GL_VERSION));
        PGT_LOG_INFO("OpenGL %s", gl_version);
        PGT_LOG_INFO("GLEW %i.%i.%i", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR,
                    GLEW_VERSION_MICRO);
        VFS::mountDirectory("/", new VDirectory("res"));
        VFS::mountDirectory("/res/", new VDirectory("fonts"));
        VFS::addFile("/res/fonts",
                     new StaticMemoryFile("ArialRoundedMt.ttf",
                                          Resources::ARIALROUNDEDMT_TTF,
                                          Resources::ARIALROUNDEDMT_TTF_SIZE));
#if 0
        VFS::mountDirectory("/res/",
                            new WindowsDirectory("shaders", "/res/shaders/"));

#else
        VFS::mountDirectory("/res/", new VDirectory("shaders"));
        VFS::addFile("/res/shaders/",
                     new StaticMemoryFile("basic.vert", Resources::BASIC_VERT,
                                          Resources::BASIC_VERT_SIZE));
        VFS::addFile("/res/shaders/",
                     new StaticMemoryFile("basic.frag", Resources::BASIC_FRAG,
                                          Resources::BASIC_FRAG_SIZE));
        VFS::addFile("/res/shaders/",
                     new StaticMemoryFile("Chunk.vert", Resources::CHUNK_VERT,
                                          Resources::CHUNK_VERT_SIZE));
        VFS::addFile("/res/shaders/",
                     new StaticMemoryFile("Chunk.frag", Resources::CHUNK_FRAG,
                                          Resources::CHUNK_FRAG_SIZE));
#endif


#ifdef FREEIMAGE_LIB
        FreeImage_Initialise();
#endif
    }

    GLFWwindow* PGTEngine_Glfw::createWindow(const window_data& data,
                                            GlfwWindow* window)
    {
        GLFWwindow* glfw_window = GlfwManager::createWindow(data);
        // TODO: make thread safe
        if (!_initialized) init();
        addWindow(window);
        return glfw_window;
    }
    void PGTEngine_Glfw::addWindow(GlfwWindow* window)
    {
        _windows.push_back(window);
    }
    void PGTEngine_Glfw::run()
    {
        try {
            _running = true;

            while (_running && _windows.size() > 0) {
                if (!_running) break;
                for (size_t i = 0; i < _windows.size(); i++) {
                    GlfwWindow* window = _windows[i];
                    bool xp =
                        (GlfwManager::requiresExtraRenderPass() == window);
                    setRenderingContext(window->getRenderingContext());
                    pollEventsForWindow(window);
                    if (window->_should_close) {
                        auto gw = window->_glfw_window;
                        delete window;
                        _windows.erase(_windows.begin() + i);
                        i--;
                    }
                    else {
                        window->internal_update();
                    }
                    if (xp) GlfwManager::performedExtraRenderPass();
                    if (!_running) break;
                }
            }
            _running = false;  // possibly true if last window closed
            GlfwManager::quit();
            PGT_LOG_INFO("Terminating...");
            for (GlfwWindow* window : _windows) {
                delete window;
            }
            _windows.clear();
#ifdef FREEIMAGE_LIB
            FreeImage_DeInitialise();
#endif
            PGT_LOG_INFO("PGTEngine_Glfw ended. All Windows CLosed");
        }
        catch (std::exception& ex) {
            messageBox(ex.what());
        }
    }

    bool PGTEngine_Glfw::isRunning()
    {
        return _running;
    }

    void PGTEngine_Glfw::setRenderingContext(IRenderingContext& rc)
    {
        if (_rendering_context != &rc) {
            _rendering_context = &rc;
            rc.setContextCurrent();
        }
    }

    IRenderingContext& PGTEngine_Glfw::getRenderingContext()
    {
        PGT_DEBUG_ASSERT(_rendering_context, "No Valid Rendering Context");
        return *_rendering_context;
    }

    void PGTEngine_Glfw::pollEventsForWindow(GlfwWindow* window)
    {
        auto& wh = GlfwManager::getWindowEventHousehold(window->_glfw_window);
        Event* ev;
        GlfwManager::lockEventQueue();
        while (wh.getEvent(&ev)) {
            GlfwManager::unlockEventQueue();
            switch (ev->ID) {
            case MouseMoveEvent::ID: {
                int x, y, xo, yo;
                x = ev->cast<MouseMoveEvent>().x;
                y = ev->cast<MouseMoveEvent>().y;
                xo = window->getCursorX();
                yo = window->getCursorY();
                window->raise(MouseMoveEvent(x, y, xo, yo));
                break;
            }
            default:
                window->raise(*ev);
                break;
            }
            delete ev;
            GlfwManager::lockEventQueue();
        }
        GlfwManager::unlockEventQueue();
    }
    void PGTEngine_Glfw::terminate()
    {
        _running = false;
    }
}