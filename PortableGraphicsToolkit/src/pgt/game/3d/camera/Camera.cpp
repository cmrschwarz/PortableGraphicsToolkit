#include "Camera.h"
namespace pgt {
    Camera::Camera()
    {
        _pos_x = 0;
        _pos_y = 0;
        _pos_z = 0;
        _pitch = 0;
        _yaw = 0;
        _pos_x_tick = 0;
        _pos_y_tick = 0;
        _pos_z_tick = 0;
        _pitch_tick = 0;
        _yaw_tick = 0;
        setProjection(60.0f, 16.0f / 9.0f);
    }
    void Camera::move(const vec3& mov)
    {
        _pos_x_tick += mov.x;
        _pos_y_tick += mov.y;
        _pos_z_tick += mov.z;
    }
    void Camera::moveInViewDirection(float forward, float sidewards,
                                     float upwards)
    {
        vec3 dir = vec3(sidewards, upwards, forward);
        dir = rotateInViewDirectionXZ(dir);
        _pos_y_tick += upwards;
        _pos_x_tick += dir.x;
        _pos_z_tick += dir.z;
    }

    pgt::vec3 Camera::rotateInViewDirection(const vec3& vin)
    {
        vec3 v = vin;
        v = mat4::rotation(-_yaw, vec3(0, 1, 0)) * v;
        v = mat4::rotation(_pitch, vec3(1, 0, 0)) * v;
        return v;
    }
    pgt::vec3 Camera::rotateInViewDirectionXZ(const vec3& vin)
    {
        vec3 v = vin;
        v = mat4::rotation(-_yaw, vec3(0, 1, 0)) * v;
        return v;
    }

    void Camera::rotate(float pitch, float yaw)
    {
        _pitch_tick += pitch;
        _yaw_tick += yaw;
    }
    void Camera::setPosition(const vec3& pos)
    {
        _pos_x_tick = 0;
        _pos_y_tick = 0;
        _pos_z_tick = 0;
        _pos_x = pos.x;
        _pos_y = pos.y;
        _pos_z = pos.z;
    }
    void Camera::setRotation(float pitch, float yaw)
    {
        _pitch = pitch;
        _pitch_tick = 0;
        _yaw = yaw;
        _yaw_tick = 0;
    }
    float Camera::getPitch()
    {
        return _pitch + _pitch_tick;
    }
    float Camera::getYaw()
    {
        return _yaw + _yaw_tick;
    }
    float Camera::getPosX()
    {
        return _pos_x + _pos_x_tick;
    }
    float Camera::getPosY()
    {
        return _pos_y + _pos_y_tick;
    }
    float Camera::getPosZ()
    {
        return _pos_z + _pos_z_tick;
    }
    vec3 Camera::getViewDirection()
    {
        vec3 fw = vec3(0, 0, 1);
        return rotateInViewDirection(fw);
    }
    void Camera::setProjection(float fov, float aspect_ratio)
    {
        _proj_matrix = mat4::perspective(0.1f, 1000.0f, fov, aspect_ratio);
    }
    const mat4& Camera::getProjectionMatrix()
    {
        return _proj_matrix;
    }
    void Camera::updateMovement()
    {
        _pitch += _pitch_tick;
        _yaw += _yaw_tick;
        if (_pitch > 90) _pitch = 90;
        if (_pitch < -90) _pitch = -90;
        if (_yaw > 360) _yaw -= 360;
        if (_yaw < -360) _yaw += 360;
        _pos_x += _pos_x_tick;
        _pos_y += _pos_y_tick;
        _pos_z += _pos_z_tick;
        _pos_x_tick = 0;
        _pos_y_tick = 0;
        _pos_z_tick = 0;
        _pitch_tick = 0;
        _yaw_tick = 0;
    }
    const mat4& Camera::getViewMatrix(float tp)
    {
        _view_matrix = mat4::rotation(_yaw + _yaw_tick * tp, vec3(0, 1, 0));
        _view_matrix =
            mat4::rotation(_pitch + _pitch_tick * tp, vec3(1, 0, 0)) *
            _view_matrix;
        _view_matrix =
            _view_matrix * mat4::translation(vec3(-_pos_x - _pos_x_tick * tp,
                                                  -_pos_y - _pos_y_tick * tp,
                                                  -_pos_z - _pos_z_tick * tp));
        // PGT_LOG_INFO("TPV: %f", tft);
        return _view_matrix;
    }
}