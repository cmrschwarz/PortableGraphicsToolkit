#pragma once

#include <pgt/graphics/plattform/opengl/voxel/renderers/static/VoxelMeshStatic.h>
#include <pgt/graphics/plattform/opengl/voxel/renderers/batched/VoxelMeshBatched.h>
namespace pgt {
    template <typename MESH_TYPE, bool SURROUNDINGS>
    class VoxelMeshUpdater;

    class VoxelMeshUpdaterStorage {
      public:
        static const int THREAD_LOCAL = 0;

      private:
        typedef VoxelMeshUpdater<VoxelMeshStatic, false> VMU_S_NS;
        typedef VoxelMeshUpdater<VoxelMeshStatic, true> VMU_S_S;
        typedef VoxelMeshUpdater<VoxelMeshBatched, false> VMU_B_NS;
        typedef VoxelMeshUpdater<VoxelMeshBatched, true> VMU_B_S;
        VMU_S_NS** _vmu_s_ns;
        VMU_S_S** _vmu_s_s;
        VMU_B_NS** _vmu_b_ns;
        VMU_B_S** _vmu_b_s;
        int _capacity;

      public:
        VoxelMeshUpdaterStorage(int capacity);
        ~VoxelMeshUpdaterStorage();
        template <typename MESH_TYPE, bool SURROUNDINGS>
        VoxelMeshUpdater<MESH_TYPE, SURROUNDINGS>* getVoxelMeshUpdater(
            int thread_id) const;
    };
}