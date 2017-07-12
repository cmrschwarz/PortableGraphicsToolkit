#include "VoxelTerrainModel.h"
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/VoxelMeshUpdater.h>
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/AsyncVoxelModelUpdater.h>
namespace pgt {
    VoxelTerrainModel::VoxelTerrainModel(VoxelModelManager* manager,
                                         VoxelMeshBatched* mesh)
        : VoxelModelBatchedAsync(manager, mesh, LENGTH, LENGTH, LENGTH),
          Collider(),
          _should_be_disabled(false)
    {
    }

    VoxelTerrainModel::~VoxelTerrainModel()
    {
    }

    bool VoxelTerrainModel::updateModelAsync(int thread_id,
                                             update_parameters* params)
    {
        VoxelMeshUpdater<VoxelMeshBatched, true>* vmu =
            getVoxelMeshUpdater<VoxelMeshBatched, true>(thread_id);
        surroundings r = surroundings(_surroundings);
        for (int i = 0; i < surroundings::COUNT; i++) {
            if (i == _surroundings.getSurroundingID(0, 0, 0)) continue;
            VoxelTerrainModel* c = _surroundings[i];
            if (c != nullptr && c->getRequesteLoadCount() > 0) return false;
        }
        // is this implicit conversion fine? --> read up
        if (_surroundings.is_bottom_chunk) {
            vmu->update<true>(this, _mesh, &r);
        }
        else {
            vmu->update(this, _mesh, &r);
        }


        if (getRequestedUpdateCount() == 1) {
            _mesh->setDisabled(_should_be_disabled);
            _mesh->requestUpdate();
        }
        return true;
    }

    void VoxelTerrainModel::updateInQueue(
        UpdatePriority p, const terrain_chunk_update_request& request,
        bool disable_while_updating)
    {
        // might cause problems becuase copy while other thread is accessing
        // TODO: evaluate
        _surroundings = request;
        if (disable_while_updating) {
            _mesh->setDisabled(true);
            _mesh->requestUpdate();
        }
        getVoxelModelUpdater()->requestUpdate(p, this, nullptr);
    }

    void VoxelTerrainModel::setPosition(const vec3& pos)
    {
        _pos = pos;
        _mesh->setTransformation(pgt::mat4::translation(pos));
    }
    const pgt::vec3& VoxelTerrainModel::getPosition() const
    {
        return _pos;
    }
    AABB VoxelTerrainModel::createSurroundingAABB()
    {
        return pgt::AABB(_pos.x, _pos.y, _pos.z, LENGTH, LENGTH, LENGTH);
    }
    bool VoxelTerrainModel::quickCheckAsAABB(pgt::AABB& c)
    {
        const vec3& po = c.getPosition();
        const vec3& so = c.getSize();
        return Collider::checkAABBCollision(_pos.x, _pos.y, _pos.z, LENGTH,
                                            LENGTH, LENGTH, po.x, po.y, po.z,
                                            so.x, so.y, so.z);
    }
    bool VoxelTerrainModel::collidesWith(pgt::AABB& c)
    {
        float cposx = c.getPosition().x - _pos.x;
        float cposy = c.getPosition().y - _pos.y;
        float cposz = c.getPosition().z - _pos.z;
        int sx = pgt::max((int)std::floor(cposx), 0);
        int sy = pgt::max((int)std::floor(cposy), 0);
        int sz = pgt::max((int)std::floor(cposz), 0);
        int tx = pgt::min((int)std::floor(cposx + c.getSize().x), LENGTH - 1);
        int ty = pgt::min((int)std::floor(cposy + c.getSize().y), LENGTH - 1);
        int tz = pgt::min((int)std::floor(cposz + c.getSize().z), LENGTH - 1);
        for (int x = sx; x <= tx; x++) {
            for (int y = sy; y <= ty; y++) {
                for (int z = sz; z <= tz; z++) {
                    if (*getVoxel(x, y, z) != VoxelContainer::AIR) return true;
                }
            }
        }
        return false;
    }

    void VoxelTerrainModel::setDisabled(bool disabled)
    {
        _should_be_disabled = disabled;
        _mesh->setDisabled(disabled);
    }
}