#pragma once

namespace pgt {
    template <bool LOAD>
    class AsyncVoxelModelUpdater;
    typedef AsyncVoxelModelUpdater<true> VoxelModelLoader;
    typedef AsyncVoxelModelUpdater<false> VoxelModelUpdater;
    template <typename MESH_TYPE, bool SURROUNDINGS>
    class VoxelMeshUpdater;
    class VoxelTerrainModel;
    enum UpdatePriority : int {
        PRIORITY_FIRST = 0,
        PRIORITY_HIGH = 0,
        PRIORITY_MEDIUM = 1,
        PRIORITY_LOW = 2,
        PRIORITY_COUNT = PRIORITY_LOW + 1,
    };
    struct update_parameters {
        update_parameters(){};
        virtual ~update_parameters(){};
    };
    class VoxelContainer;

    struct terrain_chunk_update_request : public update_parameters {
        static const int COUNT = 27;
        bool is_bottom_chunk = false;
        VoxelTerrainModel* chunks[COUNT];
        VoxelTerrainModel* operator[](int id)
        {
            return chunks[id];
        }
        static int getSurroundingID(int x, int y, int z)
        {
            int id = (x + y * 3 + z * 3 * 3) + 13;
            return id;
        }
        VoxelTerrainModel* get(int x, int y, int z)
        {
            return chunks[getSurroundingID(x, y, z)];
        }
        void set(int x, int y, int z, VoxelTerrainModel* c)
        {
            chunks[getSurroundingID(x, y, z)] = c;
        }
    };
    struct surroundings : public update_parameters {
        static const int COUNT = terrain_chunk_update_request::COUNT;
        surroundings(terrain_chunk_update_request& tcs);

        VoxelContainer* chunks[COUNT];
        VoxelContainer* operator[](int id)
        {
            return chunks[id];
        }
        static int getSurroundingID(int x, int y, int z)
        {
            return terrain_chunk_update_request::getSurroundingID(x, y, z);
        }
        VoxelContainer* get(int x, int y, int z)
        {
            return chunks[getSurroundingID(x, y, z)];
        }
        void set(int x, int y, int z, VoxelContainer* c)
        {
            chunks[getSurroundingID(x, y, z)] = c;
        }
    };
}