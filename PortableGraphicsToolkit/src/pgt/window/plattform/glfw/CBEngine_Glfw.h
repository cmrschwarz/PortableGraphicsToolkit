#pragma once
#include <pgt/utils/containers/Queue.h>
#include "GlfwWindow.h"
#include "GlfwManager.h"
#include <mutex>
#include <vector>
namespace pgt {
    class GlfwWindow;
    class PGTEngine_Glfw {
      private:
        static bool _running;
        static bool _initialized;
        static std::vector<GlfwWindow*> _windows;
        static IRenderingContext* _rendering_context;

      public:
        // WINDOWS MUST BE CREATED ON THE HEAP.
        // PGTEngine manages and destroys them for you
        static GLFWwindow* createWindow(const window_data& data, GlfwWindow* w);
        // WINDOWS MUST BE CREATED ON THE HEAP.
        // PGTEngine manages and destroys them for you
        static void addWindow(GlfwWindow* window);
        static void terminate();
        static void run();
        static bool isRunning();
        static void setRenderingContext(IRenderingContext& rc);
        static IRenderingContext& getRenderingContext();

      private:
        static void init();
        static void pollEventsForWindow(GlfwWindow* window);
    };
};
