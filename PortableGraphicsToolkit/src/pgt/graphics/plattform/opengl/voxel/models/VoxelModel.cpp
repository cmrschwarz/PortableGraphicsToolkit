#include "VoxelModel.h"
#include "VoxelModelManager.h"
namespace pgt
{
    VoxelModel::VoxelModel(VoxelModelManager* manager, int size_x, int size_y, int size_z)
        : VoxelContainer(size_x, size_y, size_z), _manager(manager)
    {
    }

    VoxelModel::~VoxelModel()
    {
    }

    VoxelModelUpdater* VoxelModel::getVoxelModelUpdater()
    {
        return _manager->_model_updater;
    }
    VoxelModelLoader* VoxelModel::getVoxelModelLoader()
    {
        return _manager->_model_loader;
    }
}