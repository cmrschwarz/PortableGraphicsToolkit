#include "VoxelModelManager.h"
#include <pgt/graphics/plattform/opengl/voxel/renderers/batched/VoxelBatchRenderer.h>
#include <pgt/graphics/plattform/opengl/voxel/renderers/static/StaticVoxelMeshRenderer.h>
#include <pgt/graphics/plattform/opengl/voxel/model_updaters/AsyncVoxelModelUpdater.h>
#include <pgt/graphics/plattform/opengl/voxel/models/VoxelMeshUpdaterStorage.h>
namespace pgt {
    VoxelModelManager::VoxelModelManager()
    {
        _index_buffer = plattform::GlIndexBuffer();
        const int required_index_count =
            VoxelBatchRenderer::REQUIRED_INDEX_BUFFER_SIZE;

        _index_buffer.initForRectangles(required_index_count);
        _batch_renderer = new VoxelBatchRenderer(_index_buffer.getID());
        _static_renderer = new StaticVoxelMeshRenderer(_index_buffer.getID());
        int vmu_tc = VoxelModelUpdater::getThreadCountSuggestion();
        int vml_tc = VoxelModelLoader::getThreadCountSuggestion();
        // +1 for synchronuous (t0)
        _voxel_mesh_updater_storage = new VoxelMeshUpdaterStorage(vmu_tc + 1);
        _model_updater = new VoxelModelUpdater(vmu_tc);
        _model_loader = new VoxelModelLoader(vml_tc);
    }
    VoxelModelManager::~VoxelModelManager()
    {
        if (_use_queued_updaters) enableQueuedUpdaters(false);
        delete _model_loader;
        delete _model_updater;
        delete _batch_renderer;
        delete _voxel_mesh_updater_storage;
    }

    VoxelMeshBatched* VoxelModelManager::createVoxelMeshBatched(
        BATCH_VARIANT variant)
    {
        return _batch_renderer->createMesh(variant);
    }

    pgt::VoxelMeshStatic* VoxelModelManager::createVoxelMeshStatic()
    {
        auto m = _static_renderer->generateVoxelMesh();
        _static_meshes.push_back(m);
        return m;
    }

    void VoxelModelManager::enableQueuedUpdaters(bool enable)
    {
        if (_use_queued_updaters == enable) return;
        _use_queued_updaters = enable;
        if (enable) {
            _model_loader->start();
            _model_updater->start();
        }
        else {
            _model_updater->stop();
            _model_loader->stop();
        }
    }

    void VoxelModelManager::setProjectionMatrix(const mat4& proj_matrix)
    {
        _batch_renderer->setProjectionMatrix(proj_matrix);
        _static_renderer->setProjectionMatrix(proj_matrix);
    }

    void VoxelModelManager::setViewMatrix(const mat4& view_matrix)
    {
        _batch_renderer->setViewMatrix(view_matrix);
        _static_renderer->setViewMatrix(view_matrix);
    }

    void VoxelModelManager::render()
    {
        auto& win = engine::getApp().getRenderingContext().getWindow();
        //  if (win.getWidth() > 640) _framebuffer.bind();

        _batch_renderer->update();
        _batch_renderer->render();
        //  _static_renderer->render();

        // if (win.getWidth() > 640)
        //      _framebuffer.unbind(win.getWidth(), win.getHeight());
    }

    void VoxelModelManager::setWireframeMode(bool val)
    {
        _batch_renderer->setWireframeMode(val);
        _static_renderer->setWireframeMode(val);
    }
}