#pragma once
#include "sdl_fwd_decls.h"
#include <SDL2/SDL.h>
#include <deque>
namespace pgt {
    namespace plattform {

        class SdlWindowEventHousehold {
        private:
            std::deque<SDL_Event> _events;
            SdlWindow* _user_window;
            SDL_Window* _sdl_win;

        public:
            SdlWindowEventHousehold(SdlWindow* user_window, SDL_Window* w)
                : _user_window(user_window), _sdl_win(w)
            {
            }

            ~SdlWindowEventHousehold() = default;

        public:
            SdlWindow* getUserWindow() const
            {
                return _user_window;
            }

            SDL_Event* peakEvent()
            {
                if (_events.empty() == true) return nullptr;
                return &_events.front();
            }

            void pushEvent(SDL_Event& e)
            {
                _events.push_back(e);
            }

            void popEvent()
            {
                _events.pop_front();
            }

            uint32_t getWindowID() const
            {
                return SDL_GetWindowID(_sdl_win);
            }
        };
    }
}