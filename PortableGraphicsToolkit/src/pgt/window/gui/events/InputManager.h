#pragma once
#include <stdint.h>
#include "PGT_KEYS.h"
#include <vector>
namespace pgt {
    class InputManager {
      private:
        static const int KEY_COUNT = 255;
        uint8_t* _keys_down;
        uint8_t* _keys_pressed;
        std::vector<uint8_t*> _keys_pressed_set;
        int _cursor_x, _cursor_y;
        int _cursor_x_rel, _cursor_y_rel;

      public:
        InputManager();
        ~InputManager();
        void wipeKeyPresses();
        bool isKeyDown(int keyCode) const;
        bool isKeyPressed(int keyCode) const;
        bool isKeyRepeated(int keyCode) const;
        int getCursorX() const;
        int getCursorY() const;
        int getCursorRelativeX();
        int getCursorRelativeY();
        char getKeyChar(unsigned char keyID, bool shift, bool alt, bool caps);

      protected:
        void setKeyDown(int keyCode, bool keyDown);
        void setCursorPositionOverride(int x, int y, int xrel, int yrel);
        void setCursorPosition(int x, int y);

      public:
        static PGT_KEYS convertGlfwKeycode(int key, int scancode, int mods);
    };
}