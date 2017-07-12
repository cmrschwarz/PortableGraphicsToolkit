#include "mat4.h"
#include <pgt/maths/maths.h>
#include <memory.h>
#define GET_ELEMENT(matrix, x, y)                                              \
    (matrix)._elements[(y) + (x)*4]  // turning Row major (x,y) to Column Major
                                     // (open gl)
namespace pgt {
    mat4::mat4()
    {
        memset(elements, 0, sizeof(elements));
    }
    mat4::mat4(float identity) : mat4()
    {
        getElement(0, 0) = 1;
        getElement(1, 1) = 1;
        getElement(2, 2) = 1;
        getElement(3, 3) = 1;
    }
    mat4::~mat4()
    {
    }

    float& mat4::getElement(int x, int y)
    {
        // we are storing row major to match opengl
        return elements[y + x * 4];
    }
    float mat4::getElement(int x, int y) const
    {
        return elements[y + x * 4];
    }

    // outside of struct
    std::ostream& operator<<(std::ostream& left, const mat4& right)
    {
        left << "mat4:" << std::endl;
        for (int y = 0; y < 4; y++) {
            left << "|";
            for (int x = 0; x < 4; x++) {
                left << right.getElement(x, y) << '|';
            }
            left << std::endl;
        }
        return left;
    }
    void mat4::operator*=(const mat4& right)
    {
        memcpy(elements, (*this * right).elements, sizeof(elements));
    }
    mat4 operator*(const mat4& left, const mat4& right)
    {
        mat4 res = mat4();
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                for (int i = 0; i < 4; i++) {
                    res.getElement(x, y) +=
                        left.getElement(i, y) * right.getElement(x, i);
                }
            }
        }
        return res;
    }
    vec3 operator*(const mat4& mat, const vec3& vec)
    {
        return vec3(
            mat.getElement(0, 0) * vec.x + mat.getElement(1, 0) * vec.y +
                mat.getElement(2, 0) * vec.z + mat.getElement(3, 0),
            mat.getElement(0, 1) * vec.x + mat.getElement(1, 1) * vec.y +
                mat.getElement(2, 1) * vec.z + mat.getElement(3, 1),
            mat.getElement(0, 2) * vec.x + mat.getElement(1, 2) * vec.y +
                mat.getElement(2, 2) * vec.z + mat.getElement(3, 2));
    }
    vec4 operator*(const mat4& mat, const vec4& vec)
    {
        return vec4(
            mat.getElement(0, 0) * vec.x + mat.getElement(1, 0) * vec.y +
                mat.getElement(2, 0) * vec.z + mat.getElement(3, 0) * vec.w,
            mat.getElement(0, 1) * vec.x + mat.getElement(1, 1) * vec.y +
                mat.getElement(2, 1) * vec.z + mat.getElement(3, 1) * vec.w,
            mat.getElement(0, 2) * vec.x + mat.getElement(1, 2) * vec.y +
                mat.getElement(2, 2) * vec.z + mat.getElement(3, 2) * vec.w,
            mat.getElement(0, 3) * vec.x + mat.getElement(1, 3) * vec.y +
                mat.getElement(2, 3) * vec.z + mat.getElement(3, 3) * vec.w);
    }
    mat4 mat4::identity()
    {
        return mat4(1.0f);
    }
    mat4 mat4::scale(const vec3& scale)
    {
        mat4 ret = mat4();
        ret.getElement(0, 0) = scale.x;
        ret.getElement(1, 1) = scale.y;
        ret.getElement(2, 2) = scale.z;
        ret.getElement(3, 3) = 1.0f;
        return ret;
    }
    mat4 mat4::perspective(float near, float far, float fov, float aspect_ratio)
    {
        mat4 ret = mat4(1);
        float q = 1.0f / tan(toRadians(0.5f * fov));
        ret.getElement(0, 0) = q / aspect_ratio;
        ret.getElement(1, 1) = q;
        ret.getElement(2, 2) = -(near + far) / (near - far);
        ret.getElement(2, 3) = 1.0f;  //-1 if you want the pos. z axis to point
                                      // out of the screen (bs)
        ret.getElement(3, 2) = (2.0f * near * far) / (near - far);
        return ret;
    }
    mat4 mat4::orthographic(float left, float right, float bottom, float top,
                            float near, float far)
    {
        mat4 ret = mat4();
        ;
        ret.getElement(0, 0) = 2.0f / (right - left);
        ret.getElement(1, 1) = 2.0f / (top - bottom);
        ret.getElement(2, 2) = 2.0f / (near - far);
        ret.getElement(3, 0) = -(left + right) / (left - right);
        ret.getElement(3, 1) = (bottom + top) / (bottom - top);
        ret.getElement(3, 2) = (far + near) / (far - near);
        ret.getElement(3, 3) = 1.0f;
        return ret;
    }
    mat4 mat4::translation(const vec3& translation)
    {
        mat4 ret = mat4(1.0f);
        ret.getElement(3, 0) = translation.x;
        ret.getElement(3, 1) = translation.y;
        ret.getElement(3, 2) = translation.z;
        return ret;
    }
    mat4 mat4::rotation(float angle, const vec3& axis)
    {
        mat4 ret(1.0f);
        float r = toRadians(angle);
        float c = cos(r);
        float s = sin(r);
        float omc = 1.0f - c;
        float x = axis.x;
        float y = axis.y;
        float z = axis.z;
        ret.getElement(0, 0) = x * omc + c;
        ret.getElement(1, 0) = y * x * omc + z * s;
        ret.getElement(2, 0) = x * z * omc - y * s;
        ret.getElement(0, 1) = x * y * omc - z * s;
        ret.getElement(1, 1) = y * omc + c;
        ret.getElement(2, 1) = y * z * omc + x * s;
        ret.getElement(0, 2) = x * z * omc + y * s;
        ret.getElement(1, 2) = y * z * omc - x * s;
        ret.getElement(2, 2) = z * omc + c;
        return ret;
    }
}