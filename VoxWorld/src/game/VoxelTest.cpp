#include "VoxelTest.h"
#include <pgt/window/plattform/sdl/SdlApp.h>
#include <game/world/World.h>
#include <pgt/graphics/plattform/opengl/2d/GlRenderer2D.h>
#include <pgt/game/3d/camera/FPSCameraController.h>
#include <pgt/graphics/plattform/opengl/voxel/renderers/batched/VoxelBatchRenderer.h>
#include <pgt/graphics/image/Image.h>
#include <pgt/io/filesystem/FileSystem.h>
#include <pgt/graphics/plattform/opengl/res/PGTResourceManager.h>
namespace game {
    pgt::VoxelModel* _player;
    using namespace pgt;
    PGT_DEBUG_ONLY(bool first_instance = true;)
    pgt::VoxelModelManager* _model_manager;
    World* _world;
    FPSCameraController* _cam;
    pgt::MovementChecker<pgt::AABB>* _move_checker;


    bool _disable_updates = false;

    VoxelTest::VoxelTest()
        : GameWindow(makeHints()),
          _rndr_2d(),
          _font("ArialRoundedMT", 16,
                pgt::MemoryStreamReader(
                    pgt::PGTResourceManager::ARIALROUNDEDMT_TTF,
                    pgt::PGTResourceManager::ARIALROUNDEDMT_TTF_SIZE)),
          _tex(640, 480, true),
          _frmb(_tex.getWidth(), _tex.getHeight(), false, true, nullptr,
                &_tex) {
        PGT_DEBUG_ASSERT(first_instance,
                        "ONLY ONE INSTANCE OF THE VoxelTest WINDOW IS ALLOWED");
        PGT_DEBUG_ONLY(first_instance = false);
        init();
    }


    void VoxelTest::onTick() {
        if (getCurrentTick() == 0)
            setTitle(
                makeStr("CUBE TALES    FPS: %i | Renderdistance (%i * %i * %i) "
                        "=> %i Chunks rendering",
                        getFPS(), l, l, h, l * l * h));
        _cam->updateMovement();
        vec3 mov = _cam->getMoveRequest();
        pgt::AABB coll = pgt::AABB(_cam->getPosX() - 0.4f, _cam->getPosY() - 1.5f,
                                 _cam->getPosZ() - 0.4f, 0.8f, 2.0f, 0.8f);
        if (_collision) {
            _move_checker->setMovingOperation(&coll, mov);
            _world->giveColliders(_move_checker);
            mov = _move_checker->getResultingMove();
        }
        _cam->move(mov);
        if (!_disable_updates) {
            _world->update((int)(_cam->getPosX() / Chunk::LENGTH),
                           (int)(_cam->getPosY() / Chunk::LENGTH),
                           (int)(_cam->getPosZ() / Chunk::LENGTH),
                           getCurrentTick());
        }
    }
    pgt::Color getColorBool(bool val) {
        return (val) ? pgt::Color::GREEN : pgt::Color::RED;
    }
    std::string& getStringBool(bool val) {
        static std::string str_on = "on";
        static std::string str_off = "off";
        return (val) ? str_on : str_off;
    }
    void VoxelTest::onRender() {
        _model_manager->setViewMatrix(_cam->getViewMatrix());
        if (!_collision) {
           engine::getApp().getRenderingContext().setFramebuffer(_frmb);
            _model_manager->render();
            engine::getApp().getRenderingContext().setDefaultFramebuffer();
        }
        _model_manager->render();


        _rndr_2d.begin();
        if (!_collision)
            _rndr_2d.drawTexture(_tex,
                                 pgt::vec2i(getWidth() - 640, getHeight() - 480),
                                 pgt::vec2i(640, 480));
        _rndr_2d.setColor(Color::GREEN);
        // FPS, TPS
        _rndr_2d.drawString(pgt::makeStr("FPS: %i", getFPS()),
                            pgt::vec2i(10, 30));
        _rndr_2d.drawString(pgt::makeStr("TPS: %i", getTPS()),
                            pgt::vec2i(10, 50));
        // CHUNK COUNT
        _rndr_2d.drawString(
            pgt::makeStr(
                "Chunk Count (%i * %i * %i) = %i", _world->getWidth(),
                _world->getWidth(), _world->getHeight(),
                _world->getWidth() * _world->getWidth() * _world->getHeight()),
            pgt::vec2i(10, 70));
        _rndr_2d.drawString(
            pgt::makeStr("Chunk Memory Usage: [(%i * %i * %i) * (%i * %i * %i) "
                        "* 2] = %.2f MB",
                        _world->getWidth(), _world->getWidth(),
                        _world->getHeight(), Chunk::LENGTH, Chunk::LENGTH,
                        Chunk::LENGTH,
                        (float)_world->getWidth() * (float)_world->getWidth() *
                            (float)_world->getHeight() * Chunk::LENGTH *
                            Chunk::LENGTH * Chunk::LENGTH * 2 / (2 << 20)),
            pgt::vec2i(10, 90));

        // COLLISION DETECTION
        _rndr_2d.drawString("Collision detection (F2): ",
                            pgt::vec2i(getWidth() - 230, 30));
        _rndr_2d.setColor(getColorBool(_collision));
        _rndr_2d.drawString(getStringBool(_collision),
                            pgt::vec2i(getWidth() - 50, 30));
        _rndr_2d.setColor(Color::GREEN);
        // MOVING TERRAIN
        _rndr_2d.drawString("Moving Terrain (F3): ",
                            pgt::vec2i(getWidth() - 230, 50));
        _rndr_2d.setColor(getColorBool(!_disable_updates));
        _rndr_2d.drawString(getStringBool(!_disable_updates),
                            pgt::vec2i(getWidth() - 50, 50));
        _rndr_2d.setColor(Color::GREEN);
        // WIREFRAME
        _rndr_2d.drawString("Wireframe (F4): ",
                            pgt::vec2i(getWidth() - 230, 70));
        _rndr_2d.setColor(getColorBool(_wireframe));
        _rndr_2d.drawString(getStringBool(_wireframe),
                            pgt::vec2i(getWidth() - 50, 70));
        _rndr_2d.setColor(Color::GREEN);
        engine::internal::checkGLErrors();
        _rndr_2d.end();
        engine::internal::checkGLErrors();
    }

    pgt::window_creation_hints VoxelTest::makeHints() {
        pgt::window_creation_hints hints;
        hints.width = 640;
        hints.height = 360;
        hints.title = "Cube Tales";
        hints.resizable = true;
        hints.tps = 30;
        hints.vSync = false;
        hints.fullscreen = false;
        return hints;
    }

    void VoxelTest::init() {
        setMouseGrab(true);
        _cam = new FPSCameraController(this);
        _model_manager = new pgt::VoxelModelManager();
#if PGT_DEBUG
        l = 8;
        h = 3;
#else
        l = 40;
        h = 8;
#endif
        _world = new World(l, h, _model_manager);
        float cMiddle = (float)0.5f * _world->getWidth() * Chunk::LENGTH;
        float hOver = (float)(_world->getHeight() + 2) * Chunk::LENGTH;
        _cam->setPosition(vec3(cMiddle, hOver, cMiddle));
        _model_manager->setProjectionMatrix(_cam->getProjectionMatrix());
        _model_manager->enableQueuedUpdaters(true);
        _move_checker = new MovementChecker<pgt::AABB>();
        _rndr_2d.setFont(_font);
    }

    void VoxelTest::onKeyDown(KeyDownEvent& ke) {
        if (ke.key == pgt::KEY_F1) setFullscreen(!isFullscreen());
        if (ke.key == KEY_F4) {
            _wireframe = !_wireframe;
            _model_manager->setWireframeMode(_wireframe);
        }
        if (ke.key == pgt::KEY_F3) _disable_updates = !_disable_updates;
        if (ke.key == pgt::KEY_F2) {
            _collision = !_collision;
        }
        if (ke.key == pgt::KEY_F8) _world->reload();
        if (ke.key == pgt::KEY_ESCAPE) {
            PGT_DEBUG_ONLY(first_instance = true);
            pgt::engine::terminateApp();
        }
        if (ke.key == KEY_F9) {
            _tex.setImage(pgt::Image(pgt::FileStreamReader(
                "C:/Users/Christian/Desktop/Diagram_2.png")));
        }
    }

    VoxelTest::~VoxelTest() {
        delete _model_manager;
        delete _world;
        delete _cam;
        delete _move_checker;
    }
}  // namespace game