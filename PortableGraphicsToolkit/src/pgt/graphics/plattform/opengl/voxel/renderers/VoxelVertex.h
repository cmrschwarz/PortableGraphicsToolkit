#pragma once
#include <pgt/maths/maths.h>
#include <pgt/utils/primitives.h>

namespace pgt {
    enum BlockFace : int {
        TOP = 0,
        BOTTOM = 1,
        LEFT = 2,
        RIGHT = 3,
        FRONT = 4,
        BACK = 5
    };
    struct VoxelVertex {
      private:
        vec3 _position;
        // 0XBGR
        uint16_t _color;

        uint16_t _multipurpose;

      public:
        VoxelVertex& setPosition(const vec3& position);
        const vec3& getPosition() const;

        VoxelVertex& setColor(uint16_t color);
        VoxelVertex& setColor(const vec3& color);
        VoxelVertex& setColorRound(const vec3& color);
        // Format: RGB (BBBBGGGGGRRRR Bin)
        uint16_t getColor() const;
        // Format: rgba (xyzw)
        const vec3 getColorV3() const;
        VoxelVertex& setAmbient(uint16_t ambient);
        uint16_t getAmbient() const;
		VoxelVertex&  setWidth(int w);
		VoxelVertex&  setHeight(int h);
        // this represents the normal vector
        VoxelVertex& setFace(BlockFace face);
        BlockFace getFace() const;

        VoxelVertex getTransformed(const mat4& transform) const;

        static void formatCurrentArrayBuffer();
    };
}