#pragma once
#include <pgt/game/3d/camera/FPSCameraController.h>
#include <pgt/graphics/plattform/opengl/GLShader.h>
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelContainer.h>
#include <pgt/graphics/plattform/opengl/voxel/renderers/static/VoxelMeshStatic.h>
namespace pgt {
    class StaticVoxelMeshRenderer {
      private:
        GLuint _ibo;
        plattform::GlShader* _shader;
        mat4 _view;
        mat4 _projection;
        bool _wireframe;
        std::vector<VoxelMeshStatic*> _meshes;

      public:
        StaticVoxelMeshRenderer(GLuint ibo);
        ~StaticVoxelMeshRenderer();
        void render();
        void setWireframeMode(bool wf);
        void setProjectionMatrix(const mat4& proj);
        void setViewMatrix(const mat4& view);
        VoxelMeshStatic* generateVoxelMesh();

      private:
        void begin();
        void end();
    };
}