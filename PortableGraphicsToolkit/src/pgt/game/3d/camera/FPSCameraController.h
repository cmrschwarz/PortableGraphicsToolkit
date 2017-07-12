#pragma once
#include <pgt/game/3D/camera/Camera.h>
#include <pgt/window/gui/events/Inputmanager.h>
#include <pgt/window/window.h>
namespace pgt {
    // a simple FPS player that can be implemented pretty quickly
    class FPSCameraController : public Camera {
      private:
        Camera _camera;
        GameWindow* _window;
        float _movement_speed;
        float _sprint_speed;
        float _rotating_speed;

      public:
        FPSCameraController(GameWindow* w);
        ~FPSCameraController();
        // checks for inputs and handles them. should be called once per tick
        vec3 getMoveRequest();
        const mat4& getProjectionMatrix();
        const mat4& getViewMatrix();
    };
}