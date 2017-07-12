#pragma once
#include "VoxelMeshBatched.h"
#include <pgt/graphics/plattform/opengl/GlShader.h>
namespace pgt {
    class VoxelBatchRenderer {
        friend class VoxelBatch;

      private:
        GLuint _ibo;
        std::vector<VoxelBatch*>* _batch_variants[(int)(BATCH_VARIANT::COUNT)];
        std::vector<VoxelMeshBatched*> _meshes_to_move;
        plattform::GlShader* _shader;
        mat4 _view;
        mat4 _projection;
        bool _wireframe = false;

      public:
        VoxelBatchRenderer(GLuint ibo);
        ~VoxelBatchRenderer();
        static const int BATCH_BUFFER_VERTEX_CAPACITY = 30000;
        static const int REQUIRED_INDEX_BUFFER_SIZE =
            BATCH_BUFFER_VERTEX_CAPACITY * 6;

      private:
        void moveMeshes();
        void updateBuffers();
        void renderBuffers();

      public:
        void setWireframeMode(bool wf);
        void setProjectionMatrix(const mat4& proj);
        void setViewMatrix(const mat4& view);
        void render();
        // call once a frame before render
        void update();
        VoxelMeshBatched* createMesh(BATCH_VARIANT variant);
    };
}