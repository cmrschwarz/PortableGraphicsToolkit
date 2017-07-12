#include "Chunk.h"
#include <pgt/maths/random/SimplexNoise.h>
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/AsyncVoxelModelUpdater.h>
#include <memory.h>
#include <pgt/graphics/Color.h>
namespace game {
    struct loading_params : pgt::update_parameters {
        int world_height;
    };

    Chunk::Chunk(pgt::VoxelModelManager* manager, pgt::VoxelMeshBatched* mesh)
        : pgt::VoxelTerrainModel(manager, mesh) {}

    bool Chunk::loadModelAsync(int thread_id, pgt::update_parameters* params) {
        loading_params* lpar = (loading_params*)params;
        memset(_blocks, AIR, LENGTH * LENGTH * LENGTH * sizeof(uint16_t));
        static pgt::SimplexNoise _noise;
        uint16_t* ycolors = new uint16_t[lpar->world_height];

        for (int y = 0; y < lpar->world_height; y++) {
            float k = 4 * (float)(y) / (lpar->world_height);
            pgt::vec3 c;
            c.x = (pgt::clamp(pgt::min(k - 1.5f, -k + 4.5f), 0.0f, 1.0f));
            c.y = (pgt::clamp(pgt::min(k - 0.5f, -k + 3.5f), 0.0f, 1.0f));
            c.z = (pgt::clamp(pgt::min(k + 0.5f, -k + 2.0f), 0.0f, 1.0f));
            ycolors[y] = pgt::Color(c).to16Bit();
        }

        for (int x = 0; x < Chunk::LENGTH; x++) {
            for (int z = 0; z < Chunk::LENGTH; z++) {
                float nx = _pos.x / 32 + x / (float)32;
                float nz = _pos.z / 32 + z / (float)32;
                float noise_comb =
                    _noise.noise(nx / 35.0f, nz / 35.0f) +
                    0.6f * _noise.noise(nx / 20.0f, nz / 20.0f) +
                    0.35f * _noise.noise(nx / 12.0f, nz / 12.0f) +
                    0.1f * _noise.noise(nx / 3.0f, nz / 3.0f);
                noise_comb /= (1.0f + 0.6f + 0.35f + 0.1f);  // between [-1 ; 1]
                noise_comb = (noise_comb + 1) / 2.0f;        // [0;1]
                int y_res = (int)std::round(
                    noise_comb *
                    lpar->world_height);  //[0,height] //what we wanted
                int y_offset = _pos.y;
                y_res -= y_offset;
                for (int y = 0; y < y_res && y < Chunk::LENGTH; y++) {
                    setVoxel(x, y, z, ycolors[y + y_offset]);
                }
            }
        }
        int i = 0;
        delete[] ycolors;
        for (int i = 0; i < Chunk::LENGTH; i++) {
            //  *getVoxel(15, i, 15) = 0x7E0;
        }
        delete lpar;
        return true;
    }

    void Chunk::loadInQueue(pgt::UpdatePriority p, int height) {
        loading_params* lpars = new loading_params();
        lpars->world_height = height;
        getVoxelModelLoader()->requestUpdate(p, this, lpars);
    }

    void Chunk::requestUpdate() {
        _mesh->requestUpdate();
    }

    void Chunk::setChunkPosition(int x, int y, int z) {
        setPosition(
            pgt::vec3((float)x * LENGTH, (float)y * LENGTH, (float)z * LENGTH));
    }
}  // namespace game