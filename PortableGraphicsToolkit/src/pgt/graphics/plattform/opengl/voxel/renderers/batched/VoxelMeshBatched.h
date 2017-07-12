#pragma once
#include <pgt/graphics/plattform/opengl/voxel/renderers/VoxelVertex.h>
#include <vector>
#include "VoxelBatch.h"
namespace pgt {
    class VoxelMeshBatched {
        friend class VoxelBatch;
        friend class VoxelBatchRenderer;

      public:
        const BATCH_VARIANT variant;

      private:
        mat4 _transformation;
        std::vector<VoxelVertex> _vertices;
        size_t _pos_in_buffer;
        size_t _submitted_vertex_count;
        bool _requires_update;
        bool _clears_queue_after_update = false;
        bool _disabled;
        VoxelBatch* _parent_batch;

      private:
        VoxelMeshBatched(BATCH_VARIANT variant);

      public:
        virtual ~VoxelMeshBatched();

      public:
        const mat4& getTransformation() const;
        void setTransformation(const mat4& transform);

        int getVertexCount() const;

        void setDisabled(bool disabled);
        bool getDisabled() const;

        void add(const VoxelVertex& vert);
        void clear();
        void clearAndFree();

        bool requiresUpdate();
        void setClearsQueueAfterUpdate(bool cas);
        bool getClearsQueueAfterUpdate() const;

        void requestUpdate();
    };
}