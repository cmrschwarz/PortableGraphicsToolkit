#pragma once
#include "VoxelModel.h"
#include <pgt/graphics/plattform/opengl/voxel/renderers/batched/VoxelMeshBatched.h>
namespace pgt {
    class VoxelModelBatched : public VoxelModel {
      protected:
        VoxelMeshBatched* _mesh;

      public:
        VoxelModelBatched(VoxelModelManager* manager, VoxelMeshBatched* mesh,
                          int size_x, int size_y, int size_z);
        virtual ~VoxelModelBatched();

      public:
        virtual const mat4& getTransformation() const override;
        virtual bool getDisabled() const override;
        virtual void setDisabled(bool disabled) override;
    };
}