#include "VoxelModelBatched.h"

namespace pgt {
    VoxelModelBatched::VoxelModelBatched(VoxelModelManager* manager,
                                         VoxelMeshBatched* mesh, int size_x,
                                         int size_y, int size_z)
        : VoxelModel(manager, size_x, size_y, size_z), _mesh(mesh)
    {
        _mesh->setClearsQueueAfterUpdate(true);
    }

    VoxelModelBatched::~VoxelModelBatched()
    {
        delete _mesh;
    }

    const mat4& VoxelModelBatched::getTransformation() const
    {
        return _mesh->getTransformation();
    }

    bool VoxelModelBatched::getDisabled() const
    {
        return _mesh->getDisabled();
    }

    void VoxelModelBatched::setDisabled(bool disabled)
    {
        _mesh->setDisabled(disabled);
    }
}
