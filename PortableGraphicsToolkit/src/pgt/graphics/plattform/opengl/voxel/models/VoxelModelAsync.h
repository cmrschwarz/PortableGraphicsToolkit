#pragma once
// These models are NOT required or even desirable to have synchronuous updating
// capabilitys.
// Because in that case one would have race conditions between the synchronuous
// update request and the async ones
#include <mutex>
#include <atomic>
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/SharedDataStructs.h>

namespace pgt {

    class VoxelModelAsync {
        template <bool LOAD>
        friend class AsyncVoxelModelUpdater;

      private:
        std::atomic_int _requested_loads;
        std::atomic_int _requested_updates;
        std::mutex _busy;
	public:
		VoxelModelAsync();
      private:
        bool carryOutAsyncModelUpdate(int thread_id, update_parameters* params);
        bool carryOutAsyncModelLoad(int thread_id, update_parameters* params);

        void registerLoadRequest();
        void registerUpdateRequest();

      protected:
        virtual bool updateModelAsync(int thread_id,
                                      update_parameters* params) = 0;
        virtual bool loadModelAsync(int thread_id,
                                    update_parameters* params) = 0;

        int getRequestedUpdateCount() const;
        int getRequesteLoadCount() const;

      public:
    };
}
