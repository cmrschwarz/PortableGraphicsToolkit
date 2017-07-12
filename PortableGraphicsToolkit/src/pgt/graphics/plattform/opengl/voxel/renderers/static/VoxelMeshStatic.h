#pragma once
#include <pgt/graphics/plattform/opengl/voxel/renderers/VoxelVertex.h>
#include <vector>
namespace pgt {
    class VoxelMeshStatic {
        friend class StaticVoxelMeshRenderer;

      private:
        std::vector<VoxelVertex> _vertices;
        int _vertex_count;
        mat4 _transformation_matrix;
        GLuint _vao, _vbo;
        bool _disabled;
        bool _requires_update;
        bool _clears_queue_after_update = false;

      public:
        ~VoxelMeshStatic();

      public:
        const mat4& getTransformation();
        void setTransformation(const mat4& transform);

        int getVertexCount() const;

        void setDisabled(bool disabled);
        bool getDisabled() const;

        void add(const VoxelVertex& vertex);
        void clear();
        void clearAndFree();


        bool requiresUpdate();
        void setClearsQueueAfterUpdate(bool value);
        bool getClearsQueueAfterUpdate() const;

        void requestUpdate();

      private:  // for the friend class
        VoxelMeshStatic();
        GLuint getVao();
        void update();
    };
}