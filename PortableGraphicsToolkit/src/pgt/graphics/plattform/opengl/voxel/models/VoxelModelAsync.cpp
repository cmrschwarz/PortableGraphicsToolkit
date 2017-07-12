#include "VoxelModelAsync.h"
namespace pgt {

	VoxelModelAsync::VoxelModelAsync():_requested_loads(0),_requested_updates(0)
	{

	}

	bool VoxelModelAsync::carryOutAsyncModelUpdate(int thread_id,
                                                   update_parameters* params)
    {
        std::lock_guard<std::mutex> lg(_busy);
        if (_requested_loads > 0) {
            return false;
        }
        if (_requested_updates > 1) {
            // scrap this update, data not up to date
            _requested_updates--;
            return true;
        }
        bool retVal = updateModelAsync(thread_id, params);
        if (retVal == true) _requested_updates--;
        return retVal;
    }

    bool VoxelModelAsync::carryOutAsyncModelLoad(int thread_id,
                                                 update_parameters* params)
    {
        std::lock_guard<std::mutex> lg(_busy);
        if (_requested_loads > 1) {
            // scrap this update, data not up to date
            _requested_loads--;
            return true;
        }
        bool retVal = loadModelAsync(thread_id, params);
        if (retVal == true) _requested_loads--;
        return retVal;
    }

    void VoxelModelAsync::registerLoadRequest()
    {
        _requested_loads++;
    }

    void VoxelModelAsync::registerUpdateRequest()
    {
        _requested_updates++;
    }
    int VoxelModelAsync::getRequestedUpdateCount() const
    {
        return _requested_updates;
    }
    int VoxelModelAsync::getRequesteLoadCount() const
    {
        return _requested_loads;
    }
}