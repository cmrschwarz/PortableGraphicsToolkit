#pragma once

#include <pgt/window/gui/events/events.h>
#include <mutex>
#include <vector>
#include <atomic>
#include <pgt/utils/containers/Queue.h>
#include <unordered_map>
#include <functional>
#include <condition_variable>
#include <thread>
struct GLFWwindow;
struct GLFWmonitor;
namespace pgt {
    class GlfwManager;  // FWD
    class GlfwWindow;   // FWD
    struct window_data {
        friend class GlfwManager;
        window_data(GlfwWindow* win, int* width, int* height, int* pos_x,
                    int* pos_y, const char* title, bool fullscreen = false,
                    GLFWwindow* context_share = nullptr)
            : user_window(win),
              width(width),
              height(height),
              pos_x(pos_x),
              pos_y(pos_y),
              title(title),
              fullscreen(fullscreen),
              context_share(context_share)
        {
        }
        GlfwWindow* user_window;
        int* width;
        int* height;
        int* pos_x;
        int* pos_y;
        const char* title;
        bool fullscreen;
        GLFWwindow* context_share;

      private:
        window_data(){};  // remember, we're friended
    };

    class GlfwWindowEventHousehold {
        friend class GlfwManager;

      private:
        pgt::Queue<Event*> _events;
        GlfwWindow* _user_window;

      public:
        bool getEvent(Event** ev)
        {
            if (_events.size() == 0) return false;
            *ev = _events.front();
            _events.pop_front();
            return true;
        }
    };
    class GlfwManager {
      private:
        typedef std::function<void(void)> CommandFunc;
        struct command {
            command(CommandFunc func, bool* commander_should_wait)
                : func(func), commander_should_wait(commander_should_wait){};
            CommandFunc func;
            bool* commander_should_wait;
        };

      private:
        static std::atomic<bool> _cancel_x_render_requests;
        static std::atomic<GlfwWindow*> _requires_x_render_pass;
        static std::mutex _x_render_path_lock;
        static std::condition_variable _x_render_path_executed;
        static std::unordered_map<GLFWwindow*, GlfwWindowEventHousehold*>
            _window_map;
        static std::mutex _window_map_lock;
        static std::vector<command> _command_queue;
        static std::mutex _command_queue_lock;
        static std::condition_variable _command_execured;

        static std::atomic<bool> _running;
        static std::thread _polling_thread;

      private:
        static void requestXRenderPath(GlfwWindowEventHousehold& hh);

      public:
        static void stopXRenderRequests();
        static void resumeXRenderRequests();
        static GlfwWindow* requiresExtraRenderPass();


        static void executeOnPollThread(CommandFunc func, bool wait = false);
        static void quit();
        static GLFWwindow* createWindow(const window_data& data);
        static GlfwWindowEventHousehold& getWindowEventHousehold(GLFWwindow* w);
        static void lockEventQueue();
        static void unlockEventQueue();

        static void performedExtraRenderPass();
        static void get_current_monitor(GLFWwindow* window,
                                        GLFWmonitor** monitor, int* width,
                                        int* height, int* x, int* y);

      private:
        static GLFWwindow* init(const window_data& data);
        static void pollingThread();
        static void performCommands();
        static void makeWindow(const window_data& request,
                               GLFWwindow** win_created);
        static void key_callback(GLFWwindow* window, int key, int scancode,
                                 int action, int mods);
        static void cursor_position_callback(GLFWwindow* window, double xpos,
                                             double ypos);
        static void mouse_button_callback(GLFWwindow* window, int button,
                                          int action, int mods);
        static void window_close_callback(GLFWwindow* window);
        static void window_size_callback(GLFWwindow* window, int width,
                                         int height);
        static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
        static void window_refresh_callback(GLFWwindow* window);
        static void window_framebuffer_size_callback(GLFWwindow* window,
                                                     int width, int height);
        static void error_callback(int id, const char* text);
    };
}