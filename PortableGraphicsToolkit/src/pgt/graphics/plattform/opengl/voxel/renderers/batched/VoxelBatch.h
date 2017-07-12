#pragma once
#include <pgt/utils/primitives.h>
#include <atomic>
#include <vector>
namespace pgt {
    class VoxelBatchRenderer;
    class VoxelMeshBatched;
    enum class BATCH_VARIANT : int {
        RARELY_UPDATING = 0,
        FREQUENTLY_UPDATING = 1,
        COUNT = FREQUENTLY_UPDATING + 1,
    };
    class VoxelBatch {
        friend class VoxelMeshBatched;

      private:
        VoxelBatchRenderer* _renderer;
        std::vector<VoxelMeshBatched*> _meshes;
        GLuint _vao, _vbo;
        size_t _vertex_count;
        std::atomic<size_t> _vertex_count_after_update;
        bool _requires_update;

      public:
        VoxelBatch(VoxelBatchRenderer* renderer);
        ~VoxelBatch();

      public:
        // call this before trying to add a mesh to make sure that the assumed
        // free space is correct
        bool tryAddMesh(VoxelMeshBatched* mesh);
        void update();
        void render();
    };
}