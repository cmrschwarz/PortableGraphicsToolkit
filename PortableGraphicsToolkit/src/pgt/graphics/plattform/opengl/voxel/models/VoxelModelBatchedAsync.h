#pragma once
#include "VoxelModelBatched.h"
#include "VoxelModelAsync.h"
namespace pgt {
    class VoxelModelBatchedAsync : public VoxelModelBatched,
                                   public VoxelModelAsync {
      public:
        typedef VoxelMeshBatched MESH_TYPE;

      public:
        using VoxelModelBatched::VoxelModelBatched;
    };
}
