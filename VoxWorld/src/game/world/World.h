#pragma once
#include <pgt/game/3d/collision/MovementChecker.h>
#include <pgt/graphics/plattform/opengl/GlShader.h>
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelModelManager.h>
#include <vector>
#include <game/world/Chunk.h>
namespace game {
    class World {
    private:
    private:
        const int _length, _height;
        int _pos_x, _pos_y, _pos_z;
        std::vector<Chunk*> _chunks;

    public:
        World(int length, int height, pgt::VoxelModelManager* model_manager);
        ~World();
        void reload();
        void update(int chunk_pos_player_x, int chunk_pos_player_y,
                    int chunk_pos_player_z, int tick_nr);
        void render(pgt::VoxelBatchRenderer* renderer);
        int getWidth() const;
        int getHeight() const;

    private:
        inline int getChunkID(int x, int y, int z) {
            return x + y * _length + z * _length * _height;
        };
        // moves the world in a certain direction and requests ChunkUpdates
        // accordingly.
        // Please beginRequesting() in chunkUpdater and loader before calling
        // this
        // function
        inline Chunk* getChunk(int x, int y, int z) {
            return _chunks[getChunkID(x, y, z)];
        };
        Chunk* getChunkSafe(int x, int y, int z);
        void requestLoadingOfChunk(Chunk* c);
        void requestUpdateForChunk(Chunk* c, pgt::UpdatePriority p,
                                   bool invalidate);

    public:
        template <typename T>
        void giveColliders(pgt::MovementChecker<T>* c) {
            int sx, sy, sz, tx, ty, tz;
            pgt::AABB& bounds = c->getSimplifiedCheckingBounds();
            sx = (int)std::floor((bounds.getPosition().x) / Chunk::LENGTH);
            sy = (int)std::floor((bounds.getPosition().y) / Chunk::LENGTH);
            sz = (int)std::floor((bounds.getPosition().z) / Chunk::LENGTH);
            tx = (int)std::floor((bounds.getPosition().x + bounds.getSize().x) /
                                 Chunk::LENGTH);
            ty = (int)std::floor((bounds.getPosition().y + bounds.getSize().y) /
                                 Chunk::LENGTH);
            tz = (int)std::floor((bounds.getPosition().z + bounds.getSize().z) /
                                 Chunk::LENGTH);
            for (int x = sx; x <= tx; x++) {
                for (int y = sy; y <= ty; y++) {
                    for (int z = sz; z <= tz; z++) {
                        Chunk* chunk = getChunkSafe(x, y, z);
                        if (chunk != nullptr) {
                            c->checkAgainstCollider(chunk);
                        }
                    }
                }
            }
        }

    private:
        enum Dir : int { POS_X, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z };
        template <Dir DIR>
        int getChunkIDfromABC(int a, int b, int c) {
            switch (DIR) {
            case POS_X:
                return getChunkID(a, b, c);
            case NEG_X:
                return getChunkID(_length - a - 1, b, c);
            case POS_Y:
                return getChunkID(b, a, c);
            case NEG_Y:
                return getChunkID(b, _height - a - 1, c);
            case POS_Z:
                return getChunkID(b, c, a);
            case NEG_Z:
                return getChunkID(b, c, _length - a - 1);
            default:
                return -1;
            }
        }
        template <Dir DIR>
        void moveChunkInDir(int count) {
            Chunk* akt_chunk;
            int lena, lenb, lenc;
            lena = (DIR == POS_Y || DIR == NEG_Y) ? _height : _length;
            lenb = (DIR == POS_X || DIR == NEG_X) ? _height : _length;
            lenc = (DIR == POS_Z || DIR == NEG_Z) ? _height : _length;
            int dirx, diry, dirz;
            dirx = (DIR == POS_X) ? 1 : ((DIR == NEG_X) ? -1 : 0);
            diry = (DIR == POS_Y) ? 1 : ((DIR == NEG_Y) ? -1 : 0);
            dirz = (DIR == POS_Z) ? 1 : ((DIR == NEG_Z) ? -1 : 0);
            // one could save a few swaps here by letting x axis be emplace /
            // remove
            for (int i = 0; i < count; i++) {
                for (int c = 0; c < lenc; c++) {
                    for (int b = 0; b < lenb; b++) {
                        for (int a = 0; a < lena - 1; a++) {
                            std::iter_swap(
                                _chunks.begin() +
                                    getChunkIDfromABC<DIR>(a, b, c),
                                _chunks.begin() +
                                    getChunkIDfromABC<DIR>(a + 1, b, c));
                        }
                        akt_chunk =
                            _chunks[getChunkIDfromABC<DIR>(lena - 1, b, c)];
                        akt_chunk->setPosition(
                            pgt::vec3(akt_chunk->getPosition().x +
                                         dirx * _length * Chunk::LENGTH,
                                     akt_chunk->getPosition().y +
                                         diry * _height * Chunk::LENGTH,
                                     akt_chunk->getPosition().z +
                                         dirz * _length * Chunk::LENGTH));
                    }
                }
                _pos_x += dirx;
                _pos_y += diry;
                _pos_z += dirz;
            }
            // updating must be done afterwards because of the surroundings
            for (int c = 0; c < lenc; c++) {
                for (int b = 0; b < lenb; b++) {
                    akt_chunk = _chunks[getChunkIDfromABC<DIR>(0, b, c)];
                    akt_chunk->setDisabled(true);
                    akt_chunk->requestUpdate();

                    for (int i = pgt::max(lena - count - 1, 0); i < lena; i++) {
                        akt_chunk = _chunks[getChunkIDfromABC<DIR>(i, b, c)];
                        if (i > lena - count - 1)
                            requestLoadingOfChunk(akt_chunk);
                        int x =
                            akt_chunk->getPosition().x / Chunk::LENGTH - _pos_x;
                        int z =
                            akt_chunk->getPosition().z / Chunk::LENGTH - _pos_z;
                        if (x == 0 || x == _length - 1 || z == 0 ||
                            z == _length - 1) {
                            akt_chunk->setDisabled(true);
                            akt_chunk->requestUpdate();
                        }
                        else {
                            // temporarily reverted by invalidate parameter
                            akt_chunk->setDisabled(false);
                            requestUpdateForChunk(akt_chunk,
                                                  pgt::PRIORITY_MEDIUM, true);
                        }
                    }
                }
            }
        }
    };
};