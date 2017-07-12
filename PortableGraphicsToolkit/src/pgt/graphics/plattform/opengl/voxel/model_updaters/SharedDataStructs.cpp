#include "SharedDataStructs.h"
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelTerrainModel.h>
namespace pgt
{
    surroundings::surroundings(terrain_chunk_update_request& tcs)
    {
        {
            for (int i = 0; i < COUNT; i++)
            {
                chunks[i] = static_cast<VoxelContainer*>(tcs[i]);
            }
        }
    }
}
