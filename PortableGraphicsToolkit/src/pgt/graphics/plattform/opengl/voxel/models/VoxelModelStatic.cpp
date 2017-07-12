#include "VoxelModelStatic.h"

namespace pgt
{
    VoxelModelStatic::VoxelModelStatic(VoxelModelManager* manager, VoxelMeshStatic* mesh,
                                       int size_x, int size_y, int size_z)
        : VoxelModel(manager, size_x, size_y, size_z), _mesh(mesh)

    {
    }

    VoxelModelStatic::~VoxelModelStatic()
    {
        delete _mesh;
    }

    const pgt::mat4& VoxelModelStatic::getTransformation() const
    {
        return _mesh->getTransformation();
    }

    bool VoxelModelStatic::getDisabled() const
    {
        return _mesh->getDisabled();
    }

    void VoxelModelStatic::setDisabled(bool disabled)
    {
        _mesh->setDisabled(disabled);
    }
}
