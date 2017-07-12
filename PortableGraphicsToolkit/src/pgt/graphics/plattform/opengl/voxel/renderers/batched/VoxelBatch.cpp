#include "VoxelBatch.h"
#include "VoxelBatchRenderer.h"
#include <GL/glew.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    VoxelBatch::VoxelBatch(VoxelBatchRenderer* renderer)
        : _renderer(renderer),
          _meshes(),
          _vertex_count(0),
          _vertex_count_after_update(0),
		_requires_update(false)
    {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     VoxelBatchRenderer::BATCH_BUFFER_VERTEX_CAPACITY *
                         sizeof(VoxelVertex),
                     NULL, GL_DYNAMIC_DRAW);
        VoxelVertex::formatCurrentArrayBuffer();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer->_ibo);
        glBindVertexArray(0);
    }
    VoxelBatch::~VoxelBatch()
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        for (VoxelMeshBatched* m : _meshes) {
            delete m;
        }
    }
    bool VoxelBatch::tryAddMesh(VoxelMeshBatched* mesh)
    {
        if (_vertex_count_after_update + mesh->_submitted_vertex_count >
            VoxelBatchRenderer::BATCH_BUFFER_VERTEX_CAPACITY)
            return false;
        _meshes.push_back(mesh);
        // no requestUpdate() to not change the old buffer
        mesh->_requires_update = true;
        mesh->_submitted_vertex_count = mesh->getVertexCount();
        mesh->_parent_batch = this;
        _vertex_count_after_update += mesh->_submitted_vertex_count;
        _requires_update = true;
        return true;
    }
    void VoxelBatch::update()
    {
        if (!_requires_update) return;
        _requires_update = false;
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        VoxelVertex* buffer =
            (VoxelVertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
        PGT_ASSERT(buffer != nullptr, "ERROR: failed to map Buffer");
        VoxelVertex* buffer_pos = buffer;
        auto iter = _meshes.begin();
        VoxelMeshBatched* mesh;
        // keep non updated meshes at the beginning of the buffer where they are
        while (iter != _meshes.end()) {
            mesh = *iter;
            if (mesh->_requires_update == true) break;
            buffer_pos += mesh->_submitted_vertex_count;
            ++iter;
        }
        // take out meshes that require an update and append them at the back
        // move non updated meshes to front into the space created by meshes
        // that require an update
        // ignore the meshes that are disabled and leave them where they are
        size_t updates_performed = 0;
        while (iter != _meshes.end() - updates_performed) {
            mesh = *iter;
            if (mesh->_disabled == true) {
                mesh->_requires_update = false;
                ++iter;
                continue;
            }
            if (mesh->_requires_update == false) {
                int mesh_vertex_count = mesh->_submitted_vertex_count;
                _vertex_count += mesh_vertex_count;
                memmove(buffer_pos, buffer + mesh->_pos_in_buffer,
                        sizeof(VoxelVertex) * mesh_vertex_count);
                mesh->_pos_in_buffer = buffer_pos - buffer;
                buffer_pos += mesh_vertex_count;
                ++iter;
            }
            else {
                updates_performed++;
                if (iter == _meshes.end() - 1) {
                    *iter = mesh;
                    break;
                }
                else {
                    iter = _meshes.erase(iter);
                    _meshes.push_back(mesh);
                }
            }
        }
        // update the meshes requiring an update that are now all at the back of
        // _meshes
        while (iter != _meshes.end()) {
            mesh = *iter;
            size_t mesh_vertex_count = mesh->_submitted_vertex_count;
            size_t buffer_element_count = (buffer_pos - buffer);
            if (buffer_element_count + mesh_vertex_count >
                VoxelBatchRenderer::BATCH_BUFFER_VERTEX_CAPACITY) {
                mesh->_parent_batch = nullptr;
                _vertex_count_after_update -= mesh_vertex_count;
                PGT_LOG_INFO("Moved MESH");
                _renderer->_meshes_to_move.push_back(mesh);
                iter = _meshes.erase(iter);
                continue;
            }
            mesh->_pos_in_buffer = buffer_pos - buffer;
            for (size_t i = 0; i < mesh_vertex_count; i++) {
                *buffer_pos =
                    mesh->_vertices[i].getTransformed(mesh->_transformation);
                buffer_pos++;
            }
            mesh->_requires_update = false;
            if (mesh->getClearsQueueAfterUpdate()) mesh->clearAndFree();
            ++iter;
        }
        _vertex_count = buffer_pos - buffer;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    void VoxelBatch::render()
    {
        glBindVertexArray(_vao);
        size_t idx = (int)(_vertex_count * 1.5f);
        glDrawElements(GL_TRIANGLES, idx, GL_UNSIGNED_INT, NULL);
    }
}
