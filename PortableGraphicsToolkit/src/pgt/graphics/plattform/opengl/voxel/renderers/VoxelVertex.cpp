#include "VoxelVertex.h"
#include <GL/glew.h>
namespace pgt {
    VoxelVertex& VoxelVertex::setPosition(const vec3& position)
    {
        _position = position;
        return *this;
    }
    const vec3& VoxelVertex::getPosition() const
    {
        return _position;
    }
    uint16_t VoxelVertex::getColor() const
    {
        return _color;
    }
    const vec3 VoxelVertex::getColorV3() const
    {
        return vec3((_color & 0x1F) / (float)(0x1F + 1),
                    ((_color >> 5) & 0x3F) / (float)(0x3F + 1),
                    ((_color >> 11) & 0x1F) / (float)(0x1F + 1));
    }
    VoxelVertex& VoxelVertex::setColor(uint16_t color)
    {
        _color = color;
        return *this;
    }
    VoxelVertex& VoxelVertex::setColor(const vec3& v)
    {
        int r = (int)(v.x * 32);
        int g = (int)(v.y * 64);
        int b = (int)(v.z * 32);
        _color = (b << 11) | (g << 5) | r;
        return *this;
    }

    pgt::VoxelVertex& VoxelVertex::setColorRound(const vec3& v)
    {
        int r = (int)std::round(v.x * 32);
        int g = (int)std::round(v.y * 64);
        int b = (int)std::round(v.z * 32);
        _color = (b << 11) | (g << 5) | r;
        return *this;
    }

    VoxelVertex& VoxelVertex::setAmbient(uint16_t ambient)
    {
        // possibly &0x3 for safety
        _multipurpose = (_multipurpose & 0xFFFFFFFC) | (ambient);
        return *this;
    }
    uint16_t VoxelVertex::getAmbient() const
    {
        return (_multipurpose & 0x3);
    }

    VoxelVertex& VoxelVertex::setWidth(int w)
    {
        _multipurpose &= ((0xFFFF) ^ (0x1F << 5));
        _multipurpose |= ((w - 1) << 5);
        return *this;
    }

    VoxelVertex& VoxelVertex::setHeight(int h)
    {
        _multipurpose &= ((0xFFFF) ^ (0x1F << 10));
        _multipurpose |= ((h - 1) << 10);
        return *this;
    }

    VoxelVertex& VoxelVertex::setFace(BlockFace face)
    {
        // possibly &0x1C for safety
        _multipurpose = (_multipurpose & 0xFFFFFFE3) | ((((int)(face)) << 2));
        return *this;
    }
    BlockFace VoxelVertex::getFace() const
    {
        return (BlockFace)((_multipurpose >> 2) & 0x7);
    }
    VoxelVertex VoxelVertex::getTransformed(const mat4& transform) const
    {
        VoxelVertex transformed = *this;
        transformed._position = transform * transformed._position;
        return transformed;
    }
    void VoxelVertex::formatCurrentArrayBuffer()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            0, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelVertex),
            (const GLvoid*)offsetof(VoxelVertex, VoxelVertex::_position));
        // Notice the I!
        glVertexAttribIPointer(
            1, 1, GL_UNSIGNED_SHORT, sizeof(VoxelVertex),
            (const GLvoid*)(offsetof(VoxelVertex, VoxelVertex::_color)));
        glVertexAttribIPointer(
            2, 1, GL_UNSIGNED_SHORT, sizeof(VoxelVertex),
            (const GLvoid*)(offsetof(VoxelVertex, VoxelVertex::_multipurpose)));
    }
}
