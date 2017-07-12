#pragma once
#include <pgt/maths/maths.h>
namespace pgt {
    class Camera {
    private:
        mat4 _view_matrix;
        mat4 _proj_matrix;
        float _pitch, _yaw, _pos_x, _pos_y, _pos_z;
        float _pitch_tick, _yaw_tick, _pos_x_tick, _pos_y_tick, _pos_z_tick;

    public:
        Camera();
        ~Camera(){};

    private:
    public:
        float getPosX();
        float getPosY();
        float getPosZ();
        float getPitch();
        float getYaw();
        // sets the view direction
        void setRotation(float pitch, float yaw);
        // "teleports" the camera to a new position
        void setPosition(const vec3& pos);
        // resets the movement for the next tick. SHould be in each tick before
        // movement
        void updateMovement();
        // adds relative movement to be carried out in the current tick
        void move(const vec3& mov);
        // adds relative movement in the view direction to be carried out in the
        // current tick
        void moveInViewDirection(float forward, float sidewards, float upwards);
        // rotates a vector from world to view coordinates
        vec3 rotateInViewDirection(const vec3& v);
        // rotates a vector from world to view coordinates, but parallel to the
        // horizontal axis
        vec3 rotateInViewDirectionXZ(const vec3& v);
        // adds relative rotation to be carried out in the current tick
        void rotate(float pitch, float yaw);
        // updates the projection Matrix to fit the current screen resolution
        void setProjection(float fov, float aspect_ratio);
        // returns a normalized vector pointing in the direction that the camera
        // is
        // looking
        vec3 getViewDirection();
        // returns the view matrix.
        // the movements applied since the last updateMovement() are
        // interpolated
        // based on tick_percentage
        // tick_percentage is the approximated percentage of time passed between
        // the
        // current and the next tick
        // you can get it from  "float pgt::Window::getTickPercentage()"
        const mat4& getViewMatrix(float tick_percentage);
        const mat4& getProjectionMatrix();
    };
}