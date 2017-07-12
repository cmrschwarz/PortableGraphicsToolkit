#pragma once
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/SharedDataStructs.h>
#include <pgt/graphics/plattform/opengl/GlIndexBuffer.h>
#include <pgt/graphics/plattform/opengl/voxel/renderers/batched/VoxelBatchRenderer.h>
#include <pgt/graphics/plattform/opengl/GlFramebuffer.h>
#include <pgt/graphics/plattform/opengl/GlTexture.h>
// TODO: maybe split into 2 classes, one for static... maybe rename to
// meshManager or change functionality
namespace pgt {
    class VoxelMeshUpdaterStorage;
    class VoxelMeshBatched;
    class StaticVoxelMeshRenderer;
    class VoxelMeshStatic;

    class VoxelModelManager {
        friend class VoxelModel;

      private:
        std::vector<VoxelMeshStatic*> _static_meshes;
        StaticVoxelMeshRenderer* _static_renderer;
        plattform::GlIndexBuffer _index_buffer;
        VoxelBatchRenderer* _batch_renderer;
        VoxelMeshUpdaterStorage* _voxel_mesh_updater_storage;

        VoxelModelLoader* _model_loader;
        VoxelModelUpdater* _model_updater;
        //  plattform::GlFramebuffer _framebuffer;
        // plattform::GlTexture _shadow_texture;
        bool _use_queued_updaters;

      public:
        VoxelModelManager();
        ~VoxelModelManager();

      public:
        VoxelMeshBatched* createVoxelMeshBatched(BATCH_VARIANT variant);
        VoxelMeshStatic* createVoxelMeshStatic();
        void enableQueuedUpdaters(bool enable);
        void setProjectionMatrix(const mat4& proj_matrix);
        void setViewMatrix(const mat4& view_matrix);
        void render();
        void setWireframeMode(bool val);
    };
}
