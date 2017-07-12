#pragma once
#include <pgt/utils\primitives.h>
#include <pgt/maths\maths.h>
#include <pgt/graphics/plattform/opengl/voxel/renderers/VoxelVertex.h>
namespace pgt {
    // stores ints representing the color of a voxel.
    // Format is (in bytes)AABBGGRR
    class VoxelContainer {
      public:
        static const uint16_t AIR = 0x0000;

      public:
        const int _size_x;
        const int _size_y;
        const int _size_z;

      protected:
        uint16_t* _blocks;  // Order: along x,z,y beginning: bottom left front
      public:
        VoxelContainer(int size_x, int size_y, int size_z);
        virtual ~VoxelContainer();
        uint16_t* getVoxel(int x, int y, int z);
        void setVoxel(int x, int y, int z, uint16_t voxel);
        uint16_t* getVoxel(int id);
        int getVoxelID(int x, int y, int z);
    };
}