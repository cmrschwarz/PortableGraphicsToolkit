#include "World.h"
#include <pgt/maths/maths.h>
namespace game {
    static int _vertices = 0;
    static int _blocks = 0;

    World::World(int length, int height, pgt::VoxelModelManager* model_manager)
        : _length(length + 2),
          _height(height),
          _pos_x(0),
          _pos_y(0),
          _pos_z(0) {
        _chunks.reserve(_length * _length * _height);
        for (int z = 0; z < _length; z++) {
            for (int y = 0; y < _height; y++) {
                for (int x = 0; x < _length; x++) {
                    Chunk* c =
                        new Chunk(model_manager,
                                  model_manager->createVoxelMeshBatched(
                                      pgt::BATCH_VARIANT::FREQUENTLY_UPDATING));
                    c->setChunkPosition(x, y, z);
                    if (x == 0 || x == _length - 1 || z == 0 ||
                        z == _length - 1) {
                        c->setDisabled(true);
                    }
                    _chunks.push_back(c);
                    requestLoadingOfChunk(c);
                }
            }
        }

        for (int i = 0; i < _length * _length * _height; i++) {
            if (_chunks[i]->getDisabled()) continue;
            requestUpdateForChunk(_chunks[i], pgt::PRIORITY_MEDIUM, true);
        }
    }
    World::~World() {
        // chunks are models, model manager deletes it
    }
    void World::reload() {
        for (int i = 0; i < _length * _length * _height; i++) {
            requestUpdateForChunk(_chunks[i], pgt::PRIORITY_MEDIUM, true);
            //_chunks[i]->_requires_mesh_update++;
        }
    }

    void World::update(int px, int py, int pz, int tick_nr) {
        int dx = px - (_pos_x + (_length / 2));
        int dy = py - (_pos_y + (_height / 2));
        int dz = pz - (_pos_z + (_length / 2));
        if (dx > 1 || dx < -1 || dz > 1 || dz < -1) {
            if (dx > 1) moveChunkInDir<POS_X>(dx);
            if (dx < -1) moveChunkInDir<NEG_X>(-dx);
            // if (dy > 1) moveChunkInDir<POS_Y>(dy);
            // if (dy < -1) moveChunkInDir<NEG_Y>(-dy);
            if (dz > 1) moveChunkInDir<POS_Z>(dz);
            if (dz < -1) moveChunkInDir<NEG_Z>(-dz);
        }
    }
    void World::requestUpdateForChunk(Chunk* c, pgt::UpdatePriority p,
                                      bool invalidate) {
        int cx, cy, cz;
        // really ugly hack. TODO: find better method of doing this
        cx = c->getPosition().x / Chunk::LENGTH;
        cy = c->getPosition().y / Chunk::LENGTH;
        cz = c->getPosition().z / Chunk::LENGTH;
        pgt::terrain_chunk_update_request request;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                for (int z = -1; z <= 1; z++) {
                    Chunk* involved_chunk =
                        getChunkSafe(cx + x, cy + y, cz + z);
                    request.set(x, y, z, involved_chunk);
                }
            }
        }
        if (cy == _pos_y) request.is_bottom_chunk = true;

        c->updateInQueue(p, request, invalidate);
    }
    Chunk* World::getChunkSafe(int x, int y, int z) {
        x -= _pos_x;
        y -= _pos_y;
        z -= _pos_z;
        if (x < 0 || x >= _length || y < 0 || y >= _height || z < 0 ||
            z >= _length) {
            return nullptr;
        }
        return getChunk(x, y, z);
    }

    void World::requestLoadingOfChunk(Chunk* c) {
        c->loadInQueue(pgt::PRIORITY_MEDIUM, _height * Chunk::LENGTH);
    }

    void World::render(pgt::VoxelBatchRenderer* renderer) {
        renderer->render();
    }

    int World::getWidth() const {
        return _length;
    }

    int World::getHeight() const {
        return _height;
    }
}  // namespace game