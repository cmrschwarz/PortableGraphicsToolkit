#include "FPSCameraController.h"
namespace pgt {
    FPSCameraController::FPSCameraController(GameWindow* w) : _camera()
    {
        _window = w;
        _movement_speed = 0.25f;
        _rotating_speed = 1.0f / 15.0f;
        _sprint_speed = 5.0f;
        _camera.setProjection(60.0f, (float)(w->getWidth()) / w->getHeight());
        _camera.setPosition(vec3(0, 0, -20));
    }
    FPSCameraController::~FPSCameraController()
    {
    }
    vec3 FPSCameraController::getMoveRequest()
    {
        // ((Camera*)(this))->updateMovement();
        float dx, dy, mov_forward, mov_sideways, mov_upwards;
        dx = (float)_window->getCursorRelativeX();
        dy = (float)_window->getCursorRelativeY();
        rotate(dy * _rotating_speed, dx * _rotating_speed);

        mov_forward = 0;
        mov_sideways = 0;
        mov_upwards = 0;

        float speed =
            _window->isKeyDown(KEY_SHIFT_L) ? _sprint_speed : _movement_speed;

        if (_window->isKeyDown(KEY_W)) mov_forward += 1;
        if (_window->isKeyDown(KEY_S)) mov_forward -= 1;
        if (_window->isKeyDown(KEY_D)) mov_sideways += 1;
        if (_window->isKeyDown(KEY_A)) mov_sideways -= 1;
        if (_window->isKeyDown(KEY_SPACE)) mov_upwards += speed;
        if (_window->isKeyDown(KEY_CTRL_L)) mov_upwards -= speed;
        vec3 res;
        if (mov_forward != 0 || mov_sideways != 0) {
            res = rotateInViewDirectionXZ(vec3(mov_sideways, 0, mov_forward));
            res.normalize();
            res *= speed;
            res.y = mov_upwards;
        }
        else {
            res = vec3(0, mov_upwards, 0);
        }
        return res;
    }
    const mat4& FPSCameraController::getProjectionMatrix()
    {
        return ((Camera*)(this))->getProjectionMatrix();
    }
    const mat4& FPSCameraController::getViewMatrix()
    {
        return ((Camera*)this)->getViewMatrix(_window->getTickPercentage());
    }
}