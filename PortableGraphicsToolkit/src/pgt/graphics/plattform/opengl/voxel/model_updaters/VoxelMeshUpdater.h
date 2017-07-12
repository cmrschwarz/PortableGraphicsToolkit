#pragma once
#include <pgt/io/logger/Logger.h>
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelContainer.h>
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelTerrainModel.h>
#include "SharedDataStructs.h"
namespace pgt {
    template <typename MESH_TYPE, bool SURROUNDINGS>
    class VoxelMeshUpdater {
      private:
        enum Coordinate {
            COORD_X,
            COORD_Y,
            COORD_Z,
            COORD_A,
            COORD_B,
            COORD_C,
            D,
        };
        static const uint16_t MASK_ALL = 0xFFFF;
        static const uint16_t MASK_AMBIENTS = 0xFF0;
        static const uint16_t PR_OCCLUDED = 0x1;
        static const uint16_t PR_USED = 0x4;
        static const uint16_t PR_AIR = 0x2;

      private:
        uint16_t*
            _block_properties;  // bitfield performance bo bo. TODO: Change to
                                // boolarray or smthn
        pgt::surroundings* _surroundings;
        VoxelContainer* _chunk;
        MESH_TYPE* _output;

      public:
        VoxelMeshUpdater()
        {
            if (SURROUNDINGS)
                _block_properties = new uint16_t[VoxelTerrainModel::LENGTH *
                                                 VoxelTerrainModel::LENGTH *
                                                 VoxelTerrainModel::LENGTH];
        }
        ~VoxelMeshUpdater()
        {
        }
        template <bool IS_BOTTOM_CHUNK = false>
        void update(VoxelContainer* chunk, MESH_TYPE* output,
                    surroundings* surroundings)
        {
            _surroundings = surroundings;
            update<IS_BOTTOM_CHUNK>(chunk, output);
            _surroundings = nullptr;
        }
        template <bool IS_BOTTOM_CHUNK = false>
        void update(VoxelContainer* chunk, MESH_TYPE* output)
        {
            output->clear();
            _output = output;
            _chunk = chunk;
            if (!SURROUNDINGS) {
                _block_properties =
                    new uint16_t[chunk->_size_x * chunk->_size_y *
                                 chunk->_size_z];
            }

            for (int i = 0;
                 i < chunk->_size_x * chunk->_size_y * chunk->_size_z; i++) {
                _block_properties[i] = 0;
                if (*chunk->getVoxel(i) == VoxelContainer::AIR) {
                    setProperties(i, PR_AIR, true);
                }
            }
            updateFace<BlockFace::TOP>(_surroundings->get(0, +1, 0));
            updateFace<BlockFace::BOTTOM, IS_BOTTOM_CHUNK>(
                _surroundings->get(0, -1, 0));
            updateFace<BlockFace::LEFT>(_surroundings->get(-1, 0, 0));
            updateFace<BlockFace::RIGHT>(_surroundings->get(+1, 0, 0));
            updateFace<BlockFace::FRONT>(_surroundings->get(0, 0, -1));
            updateFace<BlockFace::BACK>(_surroundings->get(0, 0, +1));
            if (!SURROUNDINGS) {
                // TODO: optimize this so that there is a array big enough for
                // all meshes -> no
                // reallocation
                delete[] _block_properties;
            }
        }

      private:
        __forceinline void setProperties(int id, uint16_t properties,
                                         bool enable)
        {
            if (enable) {
                _block_properties[id] |= properties;
            }
            else {
                _block_properties[id] &= (MASK_ALL ^ properties);
            }
        }
        __forceinline bool getOnePropertyEnabled(int id, int properties)
        {
            return ((_block_properties[id] & properties) != 0);
        };
        __forceinline bool getAllPropertiesEnabled(int id, int properties)
        {
            return ((_block_properties[id] & properties) == properties);
        }

      private:
        template <BlockFace FACE, Coordinate COORD>
        __forceinline int getCoordfromABC(int a, int b, int c)
        {
            switch (COORD) {
            case COORD_X:
                return getABCFromCoord<FACE, COORD_A>(a, b, c);
            case COORD_Y:
                return getABCFromCoord<FACE, COORD_B>(a, b, c);
            case COORD_Z:
                return getABCFromCoord<FACE, COORD_C>(a, b, c);
            default:
                PGT_OUT_OF_RANGE_EXIT(-1);
            }
        };
        template <BlockFace FACE, Coordinate COORD>
        __forceinline int getABCFromCoord(int x, int y, int z)
        {
            switch (FACE) {
            case FRONT:
            case BACK:
                if (COORD == COORD_A) return x;
                if (COORD == COORD_B) return y;
                if (COORD == COORD_C) return z;
            case TOP:
            case BOTTOM:
                if (COORD == COORD_A) return x;
                if (COORD == COORD_B) return z;
                if (COORD == COORD_C) return y;
            case LEFT:
            case RIGHT:
                if (COORD == COORD_A) return z;
                if (COORD == COORD_B) return y;
                if (COORD == COORD_C) return x;
            default:
                PGT_OUT_OF_RANGE_EXIT(-1);
            }
        }
        template <BlockFace FACE>
        __forceinline int getBlockIDFromABC(int a, int b, int c)
        {
            if (!SURROUNDINGS) {
                return _chunk->getVoxelID(
                    getCoordfromABC<FACE, COORD_X>(a, b, c),
                    getCoordfromABC<FACE, COORD_Y>(a, b, c),
                    getCoordfromABC<FACE, COORD_Z>(a, b, c));
            }
            else {
                int x = getCoordfromABC<FACE, COORD_X>(a, b, c);
                int y = getCoordfromABC<FACE, COORD_Y>(a, b, c);
                int z = getCoordfromABC<FACE, COORD_Z>(a, b, c);
                // x+y*32+z*(32*32)
                return x | y << 5 | z << 10;
            }
        };
        template <BlockFace FACE>
        bool isNegativeDirection()
        {
            if (FACE == BlockFace::BOTTOM || FACE == BlockFace::LEFT ||
                FACE == BlockFace::FRONT)
                return true;
            return false;
        }
        template <BlockFace FACE>
        __forceinline void setSizesABC(int& a, int& b, int& c)
        {
            if (SURROUNDINGS) {
                a = VoxelTerrainModel::LENGTH;
                b = VoxelTerrainModel::LENGTH;
                c = VoxelTerrainModel::LENGTH;
            }
            else {
                a = getABCFromCoord<FACE, COORD_A>(
                    _chunk->_size_x, _chunk->_size_y, _chunk->_size_z);
                b = getABCFromCoord<FACE, COORD_B>(
                    _chunk->_size_x, _chunk->_size_y, _chunk->_size_z);
                c = getABCFromCoord<FACE, COORD_C>(
                    _chunk->_size_x, _chunk->_size_y, _chunk->_size_z);
            }
        }
        __forceinline void setSizesXYZ(int& x, int& y, int& z)
        {
            if (SURROUNDINGS) {
                x = VoxelTerrainModel::LENGTH;
                y = VoxelTerrainModel::LENGTH;
                z = VoxelTerrainModel::LENGTH;
            }
            else {
                x = _chunk->_size_x;
                y = _chunk->_size_y;
                z = _chunk->_size_z;
            }
        }
        template <BlockFace FACE, bool IS_BOTTOM_CHUNK = false>
        void updateFace(VoxelContainer* chunk_in_dir)
        {
            int size_a, size_b, size_c;
            setSizesABC<FACE>(size_a, size_b, size_c);

            const int chunk_volume = size_a * size_b * size_c;
            for (int i = 0; i < chunk_volume; i++) {
                setProperties(i, PR_OCCLUDED | PR_USED | MASK_AMBIENTS, false);
            }
            // EXCLUDE OCCLUDED BLOCKS
            int dir_offset = (isNegativeDirection<FACE>()) ? -1 : 1;
            int c_start = (isNegativeDirection<FACE>()) ? 1 : 0;
            for (int c = c_start; c < size_c - 1 + c_start; c++) {
                for (int b = 0; b < size_b; b++) {
                    for (int a = 0; a < size_a; a++) {
                        int bid = getBlockIDFromABC<FACE>(a, b, c);
                        if (*_chunk->getVoxel(getBlockIDFromABC<FACE>(
                                a, b, c + dir_offset)) != VoxelContainer::AIR) {
                            setProperties(bid, PR_OCCLUDED, true);
                        }
                    }
                }
            }
            // EXCLUDE BLOCKS OCCLUDED FROM OTHER CHUNK

            if (chunk_in_dir != nullptr) {
                int c_ch_in_dir = isNegativeDirection<FACE>() ? size_c - 1 : 0;
                int c_chunk = isNegativeDirection<FACE>() ? 0 : size_c - 1;
                for (int a = 0; a < size_a; a++) {
                    for (int b = 0; b < size_b; b++) {
                        if (*chunk_in_dir->getVoxel(getBlockIDFromABC<FACE>(
                                a, b, c_ch_in_dir)) != VoxelContainer::AIR) {
                            setProperties(
                                getBlockIDFromABC<FACE>(a, b, c_chunk),
                                PR_OCCLUDED, true);
                        }
                    }
                }
            }

            // CALCULATE AMBIENT
            calculateAmbient<FACE>();
            // GREEDY MESHING
            uint16_t group_color;
            int block_id;
            int group_ambient;
            int group_start_a, group_start_b, akt_a, akt_b, group_end_a,
                group_end_b;
            for (int c = (IS_BOTTOM_CHUNK) ? 1 : 0; c < size_c; c++) {
                for (int b = 0; b < size_b; b++) {
                    for (int a = 0; a < size_a; a++) {
                        block_id = getBlockIDFromABC<FACE>(a, b, c);
                        if (getOnePropertyEnabled(
                                block_id, PR_AIR | PR_OCCLUDED | PR_USED))
                            continue;
                        group_color = *_chunk->getVoxel(block_id);
                        if (group_color == VoxelContainer::AIR) {
                            return;
                        }
                        group_ambient = getAmbient(block_id);
                        group_start_a = a;
                        group_start_b = b;
                        akt_b = group_start_b;
                        group_end_a = size_a;
                        akt_a = group_start_a + 1;
                        while (akt_b < size_b) {
                            while (akt_a < group_end_a) {
                                block_id =
                                    getBlockIDFromABC<FACE>(akt_a, akt_b, c);
                                if (*_chunk->getVoxel(block_id) != group_color)
                                    break;
                                if (getOnePropertyEnabled(
                                        block_id,
                                        PR_AIR | PR_OCCLUDED | PR_USED))
                                    break;
                                if (getAmbient(block_id) != group_ambient)
                                    break;
                                akt_a++;
                            }
                            if (akt_b == group_start_b) group_end_a = akt_a;
                            if (akt_a != group_end_a) break;
                            akt_b++;
                            akt_a = group_start_a;
                        }
                        group_end_b = akt_b;
                        // blocks in group are now used
                        for (akt_a = group_start_a; akt_a < group_end_a;
                             akt_a++) {
                            for (akt_b = group_start_b; akt_b < group_end_b;
                                 akt_b++) {
                                setProperties(
                                    getBlockIDFromABC<FACE>(akt_a, akt_b, c),
                                    PR_USED, true);
                            }
                        }
                        addFace<FACE>(group_color, group_ambient, group_start_a,
                                      group_start_b, c, group_end_a,
                                      group_end_b);
                    }
                }
            }
        };
        template <BlockFace FACE>
        void addFace(uint16_t color, int ambient, int a, int b, int c,
                     int end_a, int end_b)
        {
            if (!isNegativeDirection<FACE>()) c++;
            VoxelVertex vert0, vert1, vert2, vert3;
            vert0.setColor(color)
                .setAmbient(getAmbientOfVertex(ambient, 0))
                .setFace(FACE)
                .setWidth(end_a - a)
                .setHeight(end_b - b);
            vert1.setColor(color)
                .setAmbient(getAmbientOfVertex(ambient, 1))
                .setFace(FACE)
                .setWidth(end_a - a)
                .setHeight(end_b - b);
            vert2.setColor(color)
                .setAmbient(getAmbientOfVertex(ambient, 2))
                .setFace(FACE)
                .setWidth(end_a - a)
                .setHeight(end_b - b);
            vert3.setColor(color)
                .setAmbient(getAmbientOfVertex(ambient, 3))
                .setFace(FACE)
                .setWidth(end_a - a)
                .setHeight(end_b - b);

            vert0.setPosition(
                vec3((float)getCoordfromABC<FACE, COORD_X>(a, b, c),
                     (float)getCoordfromABC<FACE, COORD_Y>(a, b, c),
                     (float)getCoordfromABC<FACE, COORD_Z>(a, b, c)));
            vert1.setPosition(
                vec3((float)getCoordfromABC<FACE, COORD_X>(end_a, b, c),
                     (float)getCoordfromABC<FACE, COORD_Y>(end_a, b, c),
                     (float)getCoordfromABC<FACE, COORD_Z>(end_a, b, c)));
            vert2.setPosition(
                vec3((float)getCoordfromABC<FACE, COORD_X>(end_a, end_b, c),
                     (float)getCoordfromABC<FACE, COORD_Y>(end_a, end_b, c),
                     (float)getCoordfromABC<FACE, COORD_Z>(end_a, end_b, c)));
            vert3.setPosition(
                vec3((float)getCoordfromABC<FACE, COORD_X>(a, end_b, c),
                     (float)getCoordfromABC<FACE, COORD_Y>(a, end_b, c),
                     (float)getCoordfromABC<FACE, COORD_Z>(a, end_b, c)));

            if (FACE == FRONT || FACE == RIGHT || FACE == TOP) {
                if ((vert0.getAmbient() > vert1.getAmbient() &&
                     vert0.getAmbient() > vert3.getAmbient()) ||
                    (vert2.getAmbient() > vert1.getAmbient() &&
                     vert2.getAmbient() > vert3.getAmbient())

                    || ((vert0.getAmbient() + vert2.getAmbient() >
                         vert1.getAmbient() + vert3.getAmbient()) &&
                        !((vert1.getAmbient() > vert0.getAmbient() &&
                           vert1.getAmbient() > vert2.getAmbient()) ||
                          (vert3.getAmbient() > vert0.getAmbient() &&
                           vert3.getAmbient() > vert2.getAmbient())))) {
                    VoxelVertex temp_1 = vert1;
                    VoxelVertex temp_3 = vert3;
                    vert1 = vert0;
                    vert3 = vert2;
                    vert2 = temp_1;
                    vert0 = temp_3;
                }
                _output->add(vert0);
                _output->add(vert1);
                _output->add(vert2);
                _output->add(vert3);
            }
            else {
                if ((vert1.getAmbient() > vert2.getAmbient() &&
                     vert1.getAmbient() > vert0.getAmbient()) ||
                    (vert3.getAmbient() > vert2.getAmbient() &&
                     vert3.getAmbient() > vert0.getAmbient())

                    || ((vert1.getAmbient() + vert3.getAmbient() >
                         vert0.getAmbient() + vert2.getAmbient()) &&
                        !((vert2.getAmbient() > vert1.getAmbient() &&
                           vert2.getAmbient() > vert3.getAmbient()) ||
                          (vert0.getAmbient() > vert1.getAmbient() &&
                           vert0.getAmbient() > vert3.getAmbient())))) {
                    VoxelVertex temp_1 = vert1;
                    VoxelVertex temp_3 = vert3;
                    vert1 = vert0;
                    vert3 = vert2;
                    vert2 = temp_1;
                    vert0 = temp_3;
                }
                _output->add(vert1);
                _output->add(vert0);
                _output->add(vert3);
                _output->add(vert2);
            }
        }
        template <BlockFace FACE>
        void calculateAmbient()
        {
            int size_a, size_b, size_c;
            setSizesABC<FACE>(size_a, size_b, size_c);
            for (int a = 0; a < size_a; a++) {
                for (int b = 0; b < size_b; b++) {
                    for (int c = 0; c < size_c; c++) {
                        int block_id = getBlockIDFromABC<FACE>(a, b, c);
                        if (getOnePropertyEnabled(block_id,
                                                  PR_AIR | PR_OCCLUDED))
                            continue;
                        int c_step = isNegativeDirection<FACE>() ? -1 : 1;
                        bool nab = (getBlockSafe<FACE>(a - 1, b, c + c_step) !=
                                    VoxelContainer::AIR);
                        bool nba = (getBlockSafe<FACE>(a, b - 1, c + c_step) !=
                                    VoxelContainer::AIR);
                        bool pab = (getBlockSafe<FACE>(a + 1, b, c + c_step) !=
                                    VoxelContainer::AIR);
                        bool pba = (getBlockSafe<FACE>(a, b + 1, c + c_step) !=
                                    VoxelContainer::AIR);
                        bool papb =
                            (getBlockSafe<FACE>(a + 1, b + 1, c + c_step) !=
                             VoxelContainer::AIR);
                        bool panb =
                            (getBlockSafe<FACE>(a + 1, b - 1, c + c_step) !=
                             VoxelContainer::AIR);
                        bool nanb =
                            (getBlockSafe<FACE>(a - 1, b - 1, c + c_step) !=
                             VoxelContainer::AIR);
                        bool napb =
                            (getBlockSafe<FACE>(a - 1, b + 1, c + c_step) !=
                             VoxelContainer::AIR);

                        setAmbientOfVertex(block_id, getAO(nba, nab, nanb), 0);
                        setAmbientOfVertex(block_id, getAO(pab, nba, panb), 1);
                        setAmbientOfVertex(block_id, getAO(pba, pab, papb), 2);
                        setAmbientOfVertex(block_id, getAO(nab, pba, napb), 3);
                    }
                }
            }
        }
        // compiler should be able to deduce when this is needed and loop unroll
        //(hopefully, not tested :))
        template <BlockFace FACE>
        int getBlockSafe(int a, int b, int c)
        {
            int size_x, size_y, size_z;
            setSizesXYZ(size_x, size_y, size_z);
            int x = getCoordfromABC<FACE, COORD_X>(a, b, c);
            int y = getCoordfromABC<FACE, COORD_Y>(a, b, c);
            int z = getCoordfromABC<FACE, COORD_Z>(a, b, c);
            if (x >= 0 && y >= 0 && z >= 0 && x < size_x && y < size_y &&
                z < size_z) {
                return *_chunk->getVoxel(x, y, z);
            }
            else {
                if (!SURROUNDINGS) return VoxelContainer::AIR;
                int sx = 0;
                int sy = 0;
                int sz = 0;
                if (x >= size_x) {
                    x -= size_x;
                    sx = 1;
                }
                else if (x < 0) {
                    sx = x;
                    x += size_x;
                }
                if (y >= size_y) {
                    y -= size_y;
                    sy = 1;
                }
                else if (y < 0) {
                    sy = y;
                    y += size_y;
                }
                if (z >= size_z) {
                    z -= size_z;
                    sz = 1;
                }
                else if (z < 0) {
                    sz = z;
                    z += size_z;
                }
                VoxelContainer* chunk = _surroundings->get(sx, sy, sz);
                if (chunk == NULL) return VoxelContainer::AIR;
                return *chunk->getVoxel(x, y, z);
            }
        }
        int getAO(bool side_1, bool side_2, bool corner)
        {
            if (side_1 && side_2) return 3;
            return side_1 + side_2 + corner;
        }
        void setAmbientOfVertex(int id, int ambient, int v)
        {
            int r = _block_properties[id];
            r &= (MASK_ALL ^ (0x3 << (4 + v * 2)));
            r |= (ambient << (4 + v * 2));
            _block_properties[id] = r;
        }
        int getAmbientOfVertex(int ambient, int v)
        {
            int res = (ambient >> (v * 2)) & 0x3;
            return res;
        }
        int getAmbient(int id)
        {
            return (_block_properties[id] >> 4) & 0xFF;
        }
    };
}