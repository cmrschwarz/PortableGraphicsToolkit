#pragma once
// TODO: find better name for this unit



#include <pgt/window/plattform/interface/IApp.h>
#include <pgt/graphics/plattform/interface/IRenderingContext.h>
namespace pgt {
    namespace engine {
        bool isAppInitialized();
        void initApp();
        IApp& getApp();
        void terminateApp();

        inline IRenderingContext& getRenderingContextCurrent()
        {
            return getApp().getRenderingContext();
        }
        inline Window& getWindowCurrent()
        {
            return getApp().getRenderingContext().getWindow();
        }
        namespace internal {
            void terminateAppCallback(IApp* app);
        }
        namespace internal {
            void checkGLErrors(const char* explanation = "GL ERROR");
        }
    }
}