
#include "VoxelContainer.h"
#include <GL/glew.h>
namespace pgt {

    VoxelContainer::VoxelContainer(int size_x, int size_y, int size_z)
        : _size_x(size_x), _size_y(size_y), _size_z(size_z)
    {
        int volume = _size_x * _size_y * _size_z;
        _blocks = new uint16_t[volume];
    }
    VoxelContainer::~VoxelContainer()
    {
        delete[] _blocks;
    }

    void VoxelContainer::setVoxel(int x, int y, int z, uint16_t block)
    {
        *getVoxel(x, y, z) = block;
    }
    uint16_t* VoxelContainer::getVoxel(int x, int y, int z)
    {
        return _blocks + getVoxelID(x, y, z);
    }
    uint16_t* VoxelContainer::getVoxel(int id)
    {
        return _blocks + id;
    }
    int VoxelContainer::getVoxelID(int x, int y, int z)
    {
        return x + y * _size_x + z * _size_x * _size_y;
    }
}