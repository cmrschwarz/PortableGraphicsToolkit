#pragma once
#include "sdl_fwd_decls.h"
namespace pgt {
    namespace plattform {
        struct sdl_window_data {
            friend class SdlManager;
            sdl_window_data(SdlWindow& win, SDL_Window** created,
                            SDL_GLContext* context, bool gl, int& width,
                            int& height, int& pos_x, int& pos_y,
                            const char* title, bool fullscreen = false,
                            SDL_Window* context_share = nullptr)
                : user_window(win),
                  created_window(created),
                  gl_context(context),
                  width(width),
                  height(height),
                  pos_x(pos_x),
                  pos_y(pos_y),
                  title(title),
                  fullscreen(fullscreen),
                  context_share(context_share)
            {
            }
            SdlWindow& user_window;
            int& width;
            int& height;
            int& pos_x;
            int& pos_y;
            const char* title;
            bool fullscreen;
            SDL_Window* context_share;
            SDL_Window** created_window;
            SDL_GLContext* gl_context;
        };
    }
}
