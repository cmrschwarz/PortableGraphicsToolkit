#include "VoxelMeshUpdaterStorage.h"
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/VoxelMeshUpdater.h>
namespace pgt {
    template <>
    VoxelMeshUpdaterStorage::VMU_S_NS*
    VoxelMeshUpdaterStorage::getVoxelMeshUpdater<VoxelMeshStatic, false>(
        int thread_id) const
    {
        return _vmu_s_ns[thread_id];
    }
    template <>
    VoxelMeshUpdaterStorage::VMU_S_S*
    VoxelMeshUpdaterStorage::getVoxelMeshUpdater<VoxelMeshStatic, true>(
        int thread_id) const
    {
        return _vmu_s_s[thread_id];
    }
    template <>
    VoxelMeshUpdaterStorage::VMU_B_NS*
    VoxelMeshUpdaterStorage::getVoxelMeshUpdater<VoxelMeshBatched, false>(
        int thread_id) const
    {
        return _vmu_b_ns[thread_id];
    }
    template <>
    VoxelMeshUpdaterStorage::VMU_B_S*
    VoxelMeshUpdaterStorage::getVoxelMeshUpdater<VoxelMeshBatched, true>(
        int thread_id) const
    {
        return _vmu_b_s[thread_id];
    }

    VoxelMeshUpdaterStorage::VoxelMeshUpdaterStorage(int capacity)
    {
        _capacity = capacity;
        _vmu_s_ns = new VMU_S_NS*[_capacity];
        _vmu_s_s = new VMU_S_S*[_capacity];
        _vmu_b_ns = new VMU_B_NS*[_capacity];
        _vmu_b_s = new VMU_B_S*[_capacity];

        for (int i = 0; i < _capacity; i++) {
            _vmu_s_ns[i] = new VMU_S_NS;
            _vmu_s_s[i] = new VMU_S_S;
            _vmu_b_ns[i] = new VMU_B_NS;
            _vmu_b_s[i] = new VMU_B_S;
        }
    }

    VoxelMeshUpdaterStorage::~VoxelMeshUpdaterStorage()
    {
        for (int i = 0; i < _capacity; i++) {
            delete _vmu_s_ns[i];
            delete _vmu_s_s[i];
            delete _vmu_b_ns[i];
            delete _vmu_b_s[i];
        }
        delete _vmu_s_ns;
        delete _vmu_s_s;
        delete _vmu_b_ns;
        delete _vmu_b_s;
    }
}
