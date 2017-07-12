#pragma once
#pragma once
#include "VoxelModelStatic.h"
#include "VoxelModelAsync.h"
namespace pgt
{
    class VoxelModelStaticAsync : public VoxelModelStatic, public VoxelModelAsync
    {
    public:
        using VoxelModelStatic::VoxelModelStatic;
    };
}
