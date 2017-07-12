#pragma once
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelTerrainModel.h>
namespace game {
    class Chunk : public pgt::VoxelTerrainModel {
    public:
        Chunk(pgt::VoxelModelManager* manager, pgt::VoxelMeshBatched* mesh);

    protected:
        bool loadModelAsync(int thread_id,
                            pgt::update_parameters* params) override;

    public:
        void loadInQueue(pgt::UpdatePriority p, int height);
        void requestUpdate();
        void setChunkPosition(int x, int y, int z);
    };
};  // namespace game