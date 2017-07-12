#pragma once
#include <pgt/graphics/plattform/opengl/voxel/renderers/static/VoxelMeshStatic.h>
#include "VoxelModel.h"
namespace pgt {
    class VoxelModelStatic : public VoxelModel {
      protected:
        VoxelMeshStatic* _mesh;

      public:
        VoxelModelStatic(VoxelModelManager* manager, VoxelMeshStatic* mesh,
                         int size_x, int size_y, int size_z);
        virtual ~VoxelModelStatic();

      public:
        virtual const mat4& getTransformation() const override final;
        virtual bool getDisabled() const override;
        virtual void setDisabled(bool disabled) override;
    };
}