#include "VoxelMeshBatched.h"

namespace pgt {
    VoxelMeshBatched::VoxelMeshBatched(BATCH_VARIANT v)
        : variant(v),
          _parent_batch(nullptr),
          _disabled(false),
          _pos_in_buffer(-1),
          _submitted_vertex_count(0),
          _requires_update(true),
          _transformation(mat4::identity()),
          _vertices()
    {
    }

    VoxelMeshBatched::~VoxelMeshBatched()
    {
    }
    void VoxelMeshBatched::add(const VoxelVertex& vert)
    {
        _vertices.push_back(vert);
    }

    void VoxelMeshBatched::clear()
    {
        _vertices.clear();
    }
    void VoxelMeshBatched::clearAndFree()
    {
        _vertices.clear();
        _vertices.shrink_to_fit();
    }
    void VoxelMeshBatched::requestUpdate()
    {
        int vertex_count = (_disabled) ? 0 : getVertexCount();
        if (_parent_batch != nullptr) {
            _parent_batch->_vertex_count_after_update +=
                vertex_count - _submitted_vertex_count;
            _parent_batch->_requires_update = true;
        }
        _submitted_vertex_count = vertex_count;
        _requires_update = true;
    }
    bool VoxelMeshBatched::requiresUpdate()
    {
        return _requires_update;
    }

    void VoxelMeshBatched::setClearsQueueAfterUpdate(bool cas)
    {
        _clears_queue_after_update = cas;
    }

    bool VoxelMeshBatched::getClearsQueueAfterUpdate() const
    {
        return _clears_queue_after_update;
    }

    void VoxelMeshBatched::setDisabled(bool disabled)
    {
        _disabled = disabled;
    }

    bool VoxelMeshBatched::getDisabled() const
    {
        return _disabled;
    }

    void VoxelMeshBatched::setTransformation(const mat4& transform)
    {
        _transformation = transform;
        _requires_update = true;
        if (_parent_batch != nullptr) _parent_batch->_requires_update = true;
    }
    const mat4& VoxelMeshBatched::getTransformation() const
    {
        return _transformation;
    }
    int VoxelMeshBatched::getVertexCount() const
    {
        return _vertices.size();
    }
}
