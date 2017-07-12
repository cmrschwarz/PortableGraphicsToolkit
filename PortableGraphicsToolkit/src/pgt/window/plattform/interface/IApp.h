#pragma once
#include <pgt/io/vfs/VirtualFileSystem.h>
namespace pgt {

    // class IApp
    class VDirectory;
    class IRenderingContext;
    class IApp {
    private:
        VirtualFileSystem _vfs;

    public:
        IApp() = default;
        virtual ~IApp(){};

    public:
        virtual bool isEventBased() const = 0;
        virtual void requestEventBased(bool eb) = 0;
        virtual void run() = 0;
        virtual bool isRunning() const = 0;
        virtual void setRenderingContext(IRenderingContext& rc) = 0;
        virtual IRenderingContext& getRenderingContext() const = 0;
        inline VirtualFileSystem& getVFS()
        {
            return _vfs;
        }

    public:
        virtual void terminate() = 0;
    };
}
