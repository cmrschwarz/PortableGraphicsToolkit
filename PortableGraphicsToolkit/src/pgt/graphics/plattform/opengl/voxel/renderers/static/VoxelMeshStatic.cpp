#include "VoxelMeshStatic.h"
#include <GL/glew.h>
namespace pgt {
    VoxelMeshStatic::VoxelMeshStatic()
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        VoxelVertex::formatCurrentArrayBuffer();
        glBindVertexArray(0);
    }
    VoxelMeshStatic::~VoxelMeshStatic()
    {
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }
    void VoxelMeshStatic::add(const VoxelVertex& vertex)
    {
        _vertices.push_back(vertex);
    }
    void VoxelMeshStatic::clear()
    {
        _vertices.clear();
    }

    void VoxelMeshStatic::clearAndFree()
    {
        _vertices.clear();
        _vertices.shrink_to_fit();
    }

    void VoxelMeshStatic::requestUpdate()
    {
        _requires_update = true;
    }

    bool VoxelMeshStatic::requiresUpdate()
    {
        return _requires_update;
    }

    void VoxelMeshStatic::setClearsQueueAfterUpdate(bool value)
    {
        _clears_queue_after_update = value;
    }

    bool VoxelMeshStatic::getClearsQueueAfterUpdate() const
    {
        return _clears_queue_after_update;
    }

    GLuint VoxelMeshStatic::getVao()
    {
        return _vao;
    }

    void VoxelMeshStatic::update()
    {
        _requires_update = false;
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        _vertex_count = _vertices.size();
        if (_vertex_count > 0) {
            glBufferDaclionta(GL_ARRAY_BUFFER, _vertex_count * sizeof(VoxelVertex),
                         &_vertices[0], GL_STATIC_DRAW);
        }
        else {
            glBufferData(GL_ARRAY_BUFFER, NULL, NULL, GL_STATIC_DRAW);
        }
    }

    void VoxelMeshStatic::setDisabled(bool disabled)
    {
        _disabled = disabled;
    }

    bool VoxelMeshStatic::getDisabled() const
    {
        return _disabled;
    }
    int VoxelMeshStatic::getVertexCount() const
    {
        return _vertex_count;
    }
    const mat4& VoxelMeshStatic::getTransformation()
    {
        return _transformation_matrix;
    }
    void VoxelMeshStatic::setTransformation(const mat4& transform)
    {
        _transformation_matrix = transform;
    }
}