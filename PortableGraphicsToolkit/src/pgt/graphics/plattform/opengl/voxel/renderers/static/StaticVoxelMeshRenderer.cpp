#include "StaticVoxelMeshRenderer.h"
#include <GL/glew.h>
#include <pgt/io/vfs/VirtualFileSystem.h>
namespace pgt {
    StaticVoxelMeshRenderer::StaticVoxelMeshRenderer(GLuint ibo) : _ibo(ibo)
    {
        _shader = new plattform::GlShader(
            VfsFileStreamReader("/res/shaders/chunk.vert"),
            VfsFileStreamReader("/res/shaders/chunk.frag"));
        _shader->enable();
    }

    VoxelMeshStatic* StaticVoxelMeshRenderer::generateVoxelMesh()
    {
        auto m = new VoxelMeshStatic();
        _meshes.push_back(m);
        return m;
    }

    StaticVoxelMeshRenderer::~StaticVoxelMeshRenderer()
    {
        delete _shader;
    }
    void StaticVoxelMeshRenderer::begin()
    {
        // glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        if (!_wireframe) {
            glEnable(GL_CULL_FACE);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        _shader->enable();
        _shader->setUniformMat4("uf_projection", _projection);  // suboptimal
        _shader->setUniformMat4("uf_view", _view);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    }

    void StaticVoxelMeshRenderer::end()
    {
        glBindVertexArray(0);
        _shader->disable();
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void StaticVoxelMeshRenderer::render()
    {
        begin();
        for (auto it = _meshes.begin(); it != _meshes.end(); ++it) {
            auto& mesh = **it;
            if (mesh.requiresUpdate()) mesh.update();
            if (mesh.getVertexCount() != 0 && mesh.getDisabled() == false) {
                _shader->setUniformMat4("uf_model", mesh.getTransformation());
                glBindVertexArray(mesh.getVao());
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
                int idx = (int)(mesh.getVertexCount() * 1.5);
                glDrawElements(GL_TRIANGLES, idx, GL_UNSIGNED_INT, NULL);
            }
        }
        end();
    }

    void StaticVoxelMeshRenderer::setWireframeMode(bool wf)
    {
        _wireframe = wf;
    }

    void StaticVoxelMeshRenderer::setProjectionMatrix(const mat4& proj)
    {
        _projection = proj;
    }

    void StaticVoxelMeshRenderer::setViewMatrix(const mat4& view)
    {
        _view = view;
    }
}