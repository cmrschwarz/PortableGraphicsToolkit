#pragma once
#include "VoxelModelBatchedAsync.h"
#include "VoxelModelStaticAsync.h"
#include <pgt/game/3d/Collision/AABB.h>
#include <atomic>
namespace pgt {
    class VoxelTerrainModel : public VoxelModelBatchedAsync, public Collider {
      public:
        static const uint8_t LENGTH = 32;

      protected:
        bool _should_be_disabled;
        terrain_chunk_update_request _surroundings;

      public:
        VoxelTerrainModel(VoxelModelManager* manager, VoxelMeshBatched* mesh);
        virtual ~VoxelTerrainModel();

      private:
        // for user readability. thank me later :)
        virtual bool loadModelAsync(int thread_id,
                                    update_parameters* params) override = 0;
        virtual bool updateModelAsync(int thread_id,
                                      update_parameters* params) override;

      public:
        void updateInQueue(UpdatePriority p,
                           const terrain_chunk_update_request& request,
                           bool disable_while_updating);
        bool quickCheckAsAABB(AABB& other) override;
        AABB createSurroundingAABB() override;
        bool collidesWith(AABB& c) override;
        void setDisabled(bool disabled) override;
        void setPosition(const vec3& pos) override;
        const vec3& getPosition() const override;
    };
}
