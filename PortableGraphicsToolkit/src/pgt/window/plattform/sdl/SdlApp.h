#pragma once
#include <pgt/utils/containers/Queue.h>
#include "SdlWindow.h"
#include <vector>
#include <pgt/window/plattform/interface/IApp.h>
#include <deque>
#include <mutex>
#include "sdl_window_data.h"
#include <thread>
union SDL_Event;
namespace pgt {
    namespace plattform {
        class SdlWindowEventHousehold;

        class SdlApp : public IApp {
            friend class SdlWindow;

        private:
            std::thread::id _thread_id;
            // this global (NON TLS) tracks the all sdl instances
            static std::vector<SdlApp*> _instances;
            bool _running;
			int _sdl_user_event_terminate_app;
            bool _terminated;
            bool _event_based;
            static bool _initialized;
            static std::mutex _window_creation_lock;
            std::vector<SdlWindowEventHousehold*> _window_event_households;
            IRenderingContext* _rendering_context;

        public:
            SdlApp();
            ~SdlApp();



        public:
            bool isRunning() const override;
            void run() override;
            void terminate() override;

            void setRenderingContext(IRenderingContext& rc) override;
            IRenderingContext& getRenderingContext() const override;

        private:
            void initSDL();
            void initGLEW();
            void createWindow(SdlWindow* window, const sdl_window_data& dat);

            static int eventFilter(void* userdata, SDL_Event* event);
            int pollSdlEvent(SDL_Event* e, bool wait);
            void pollEvents();
            void handleEventsForWindow(SdlWindowEventHousehold& window);

            bool isEventBased() const override;
            void requestEventBased(bool val);


        private:
            SdlWindowEventHousehold* getEventHouseHouseHoldFromID(uint32_t id);
            static PGT_KEYS convertKeyCode(int sdlk);
        };
    }
};
