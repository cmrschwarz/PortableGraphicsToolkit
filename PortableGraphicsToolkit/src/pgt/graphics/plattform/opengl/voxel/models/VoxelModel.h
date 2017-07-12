#pragma once
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelContainer.h>
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/SharedDataStructs.h>
#include "VoxelMeshUpdaterStorage.h"
#include "VoxelModelManager.h"
namespace pgt {
    // TODO: evaluate all models having asynchronous capabilities
    class VoxelModelManager;
    class VoxelModel : public VoxelContainer {
      public:
        VoxelModel(VoxelModelManager* manager, int size_x, int size_y,
                   int size_z);
        virtual ~VoxelModel();

      protected:
        VoxelModelManager* _manager;
        // Please make shure to use the threaded version in a multi threaded
        // (AsyncModel) Environment
        VoxelModelUpdater* getVoxelModelUpdater();
        VoxelModelLoader* getVoxelModelLoader();
        template <typename MESH_TYPE, bool SURROUNDINGS>
        VoxelMeshUpdater<MESH_TYPE, SURROUNDINGS>* getVoxelMeshUpdater(
            int thread_id = 0) const
        {
            return _manager->_voxel_mesh_updater_storage
                ->getVoxelMeshUpdater<MESH_TYPE, SURROUNDINGS>(thread_id);
        }

      public:
        virtual void setDisabled(bool disabled) = 0;
        virtual bool getDisabled() const = 0;
        virtual void setPosition(const vec3& pos) = 0;
        virtual const vec3& getPosition() const = 0;
        virtual const mat4& getTransformation() const = 0;
    };
}