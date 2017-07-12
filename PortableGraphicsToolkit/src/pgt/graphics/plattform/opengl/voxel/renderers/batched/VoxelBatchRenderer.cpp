#include "VoxelBatchRenderer.h"
#include <GL/glew.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    VoxelBatchRenderer::VoxelBatchRenderer(GLuint ibo) : _ibo(ibo)
    {
        _shader = new plattform::GlShader(
            VfsFileStreamReader("/res/shaders/chunk.vert"),
            VfsFileStreamReader("/res/shaders/chunk.frag"));
        for (int i = 0; i < (int)BATCH_VARIANT::COUNT; i++) {
            _batch_variants[i] = new std::vector<VoxelBatch*>();
        }
    }
    VoxelBatchRenderer::~VoxelBatchRenderer()
    {
        for (int i = 0; i < (int)BATCH_VARIANT::COUNT; i++) {
            for (VoxelBatch* b : *_batch_variants[i]) {
                delete b;
            }
            delete _batch_variants[i];
        }
        delete _shader;
    }
    VoxelMeshBatched* VoxelBatchRenderer::createMesh(BATCH_VARIANT variant)
    {
        VoxelMeshBatched* mesh = new VoxelMeshBatched(variant);
        _meshes_to_move.push_back(mesh);
        return mesh;
    }
    void VoxelBatchRenderer::moveMeshes()
    {
        bool found_buffer_to_insert;
        for (VoxelMeshBatched* m : _meshes_to_move) {
            found_buffer_to_insert = false;
            for (VoxelBatch* b : *_batch_variants[(int)m->variant]) {
                if (b->tryAddMesh(m)) {
                    found_buffer_to_insert = true;
                    break;
                }
            }
            if (!found_buffer_to_insert) {
                PGT_LOG_INFO("Added new Buffer");
                VoxelBatch* batch = new VoxelBatch(this);
                _batch_variants[(int)m->variant]->push_back(batch);
                PGT_ASSERT(batch->tryAddMesh(m),
                          "Failed to put mesh in buffer! It is bigger than the "
                          "buffersize! "
                          "(%iverts > %iverts)",
                          m->getVertexCount(),
                          VoxelBatchRenderer::BATCH_BUFFER_VERTEX_CAPACITY)
            }
        }
        _meshes_to_move.clear();
    }

    void VoxelBatchRenderer::updateBuffers()
    {
        for (int i = 0; i < (int)BATCH_VARIANT::COUNT; i++) {
            for (VoxelBatch* b : *_batch_variants[i]) {
                b->update();
                if (_meshes_to_move.size() > 0) {
                    // TODO: move meshes immediately to avoid having to reupdate
                    // SOLUTION: _buffers_to_update
                }
            }
        }
    }
    void VoxelBatchRenderer::renderBuffers()
    {
        for (int i = 0; i < (int)BATCH_VARIANT::COUNT; i++) {
            for (VoxelBatch* b : (*(_batch_variants[i]))) {
                b->render();
            }
        }
    }

    void VoxelBatchRenderer::setWireframeMode(bool wf)
    {
        _wireframe = wf;
    }

    void VoxelBatchRenderer::setProjectionMatrix(const mat4& proj)
    {
        _shader->enable();
        _projection = proj;
        _shader->setUniformMat4("uf_projection", proj);
        _shader->disable();
    }

    void VoxelBatchRenderer::setViewMatrix(const mat4& view)
    {
        _view = view;
    }
    void VoxelBatchRenderer::update()
    {
        updateBuffers();
        moveMeshes();
        updateBuffers();
    }
    void VoxelBatchRenderer::render()
    {
        if (_wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else {
            glEnable(GL_CULL_FACE);
        }
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        _shader->enable();
        _shader->setUniformMat4("uf_view", _view);
        renderBuffers();
        _shader->disable();
        glBindVertexArray(0);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        if (_wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        int gl_err = glGetError();
        PGT_DEBUG_ASSERT(gl_err == GL_NO_ERROR, "GL Error %i", gl_err);
    }
}
