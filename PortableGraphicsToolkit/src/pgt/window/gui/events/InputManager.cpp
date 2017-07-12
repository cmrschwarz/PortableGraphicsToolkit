#include "InputManager.h"
#include <GLFW/glfw3.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    InputManager::InputManager():_cursor_x_rel(0),_cursor_y_rel(0)
    {
        _keys_down = new uint8_t[KEY_COUNT];
        _keys_pressed = new uint8_t[KEY_COUNT];
        for (int i = 0; i < KEY_COUNT; i++) {
            _keys_down[i] = false;
            _keys_pressed[i] = false;
        }
    }
    InputManager::~InputManager()
    {
        delete[] _keys_down;
        delete[] _keys_pressed;
    }

    void InputManager::setKeyDown(int keyCode, bool keyDown)
    {
        if (keyCode < 0 || keyCode > KEY_COUNT) {
            PGT_LOG_WARN("INVALID KEYCODE");
            return;
        }
        _keys_down[keyCode] = keyDown;
        if (keyDown) {
            _keys_pressed[keyCode] = keyDown;
            _keys_pressed_set.push_back(&_keys_pressed[keyCode]);
        }
    }
    void InputManager::setCursorPositionOverride(int x, int y, int xrel,
                                                 int yrel)
    {
        _cursor_x_rel += xrel;
        _cursor_y_rel += yrel;
        _cursor_x = x;
        _cursor_y = y;
    }
    void InputManager::setCursorPosition(int x, int y)
    {
        int xrel = x - _cursor_x;
        int yrel = y - _cursor_y;
        _cursor_x_rel += xrel;
        _cursor_y_rel += yrel;
        _cursor_x = x;
        _cursor_y = y;
    }
    void InputManager::wipeKeyPresses()
    {
        _cursor_x_rel = 0;
        _cursor_y_rel = 0;
        for (auto it = _keys_pressed_set.begin(); it != _keys_pressed_set.end();
             ++it) {
            *(*it) = 0;
        }
        _keys_pressed_set.clear();
    }

    bool InputManager::isKeyDown(int keyCode) const
    {
        return _keys_down[keyCode];
    }

    bool InputManager::isKeyPressed(int keyCode) const
    {
        return _keys_pressed[keyCode];
    }

    bool InputManager::isKeyRepeated(int keyCode) const
    {
        if (!isKeyDown(keyCode)) return false;
        if (isKeyPressed(keyCode)) return false;
        return true;
    }

    int InputManager::getCursorX() const
    {
        return _cursor_x;
    }
    int InputManager::getCursorY() const
    {
        return _cursor_y;
    }
    int InputManager::getCursorRelativeX()
    {
        return _cursor_x_rel;
    }
    int InputManager::getCursorRelativeY()
    {
        return _cursor_y_rel;
    }

    pgt::PGT_KEYS InputManager::convertGlfwKeycode(int key, int scancode, int mods)
    {
        if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) return (PGT_KEYS)key;
        // TODO: get num keys, use mods
        if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9) return (PGT_KEYS)key;
        if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F21) {
            size_t offset = key - GLFW_KEY_F1;
            return (PGT_KEYS)(KEY_F1 + offset);
        }
        switch (key) {
        case GLFW_KEY_LEFT_CONTROL:
            return KEY_CTRL_L;
        case GLFW_KEY_RIGHT_CONTROL:
            return KEY_CTRL_R;
        case GLFW_KEY_LEFT_ALT:
            return KEY_ALT_L;
        case GLFW_KEY_RIGHT_ALT:
            return KEY_ALT_R;
        case GLFW_KEY_ESCAPE:
            return KEY_ESCAPE;
        case GLFW_KEY_SPACE:
            return KEY_SPACE;
        case GLFW_KEY_LEFT_SHIFT:
            return KEY_SHIFT_L;
        case GLFW_KEY_RIGHT_SHIFT:
            return KEY_SHIFT_R;
        case GLFW_KEY_BACKSPACE:
            return KEY_BACKSPACE;
        // TODO: check if this is correct
        case GLFW_MOUSE_BUTTON_1:
            return MBUTTON_LEFT;
        case GLFW_MOUSE_BUTTON_2:
            return MBUTTON_MIDDLE;
        case GLFW_MOUSE_BUTTON_3:
            return MBUTTON_RIGHT;
        default:
            return (PGT_KEYS)key;
        }
    }
}