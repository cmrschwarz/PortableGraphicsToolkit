#include "engine.h"
#include <pgt/window/plattform/interface/IApp.h>
#include <pgt/io/vfs/VirtualFileSystem.h>
#include <pgt/graphics/plattform/opengl/res/PGTResourceManager.h>
#include <pgt/io/vfs/OSDirectory.h>
#include <GL/glew.h>
#include <pgt/window/window.h>
#include <pgt/managed_object.h>
namespace pgt {
    namespace engine {
        static thread_local IApp* _tls_app = nullptr;

        IApp& getApp()
        {
            return *_tls_app;
        }

        void terminateApp()
        {
            getApp().terminate();
        }

        bool isAppInitialized()
        {
            return (_tls_app);
        }

        void initApp()
        {
            if (_tls_app) {
                engine::terminateApp();
            }
            _tls_app = new App();
            auto& vfs = _tls_app->getVFS();
            // TODO: make all this per app instead of per programm
            vfs.mountDirectory("/", new_mo<VDirectory>("res"));
            vfs.mountDirectory("/res/", new_mo<VDirectory>("fonts"));
            vfs.addFile(
                "/res/fonts",
                new_mo<StaticMemoryFile>(
                    "arialroundedmt.ttf", PGTResourceManager::ARIALROUNDEDMT_TTF,
                    PGTResourceManager::ARIALROUNDEDMT_TTF_SIZE));
#if 1
            vfs.mountDirectory("/res/",
				new_mo< OSDirectory>("shaders", "C:/daten_local/tech/programming/CPlusPlus/PGTEngine/VoxWorld/res/shaders"));

#else

            vfs.mountDirectory("/res/", new_mo<VDirectory>("shaders"));
            vfs.addFile("/res/shaders/",
                        new_mo<StaticMemoryFile>(
                            "basic.vert", PGTResourceManager::BASIC_VERT,
                            PGTResourceManager::BASIC_VERT_SIZE));
            vfs.addFile("/res/shaders/",
                        new_mo<StaticMemoryFile>(
                            "basic.frag", PGTResourceManager::BASIC_FRAG,
                            PGTResourceManager::BASIC_FRAG_SIZE));
            vfs.addFile("/res/shaders/",
                        new_mo<StaticMemoryFile>(
                            "Chunk.vert", PGTResourceManager::CHUNK_VERT,
                            PGTResourceManager::CHUNK_VERT_SIZE));
            vfs.addFile("/res/shaders/",
                        new_mo<StaticMemoryFile>(
                            "Chunk.frag", PGTResourceManager::CHUNK_FRAG,
                            PGTResourceManager::CHUNK_FRAG_SIZE));
#endif
        }

        void internal::terminateAppCallback(IApp* app)
        {
            if (_tls_app == app) _tls_app = nullptr;
            delete app;
        }

        void internal::checkGLErrors(const char* explanation /*= "GL ERROR"*/)
        {
            GLenum err = glGetError();
            PGT_ASSERT(err == GL_NO_ERROR, "%s: %i", explanation, err);
        }
    }
}
