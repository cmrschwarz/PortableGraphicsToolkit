#include "VfsFileStreamWriter.h"
#include "VirtualFileSystem.h"
#include <pgt/window/engine.h>
namespace pgt {

    VfsFileStreamWriter::VfsFileStreamWriter(const std::string& path)
        : _fsw(engine::getApp().getVFS().createFileStreamWriter(path))
    {
    }

    VfsFileStreamWriter::VfsFileStreamWriter(VfsFileStreamWriter&& other)
    {
        _fsw = other._fsw;
        other._fsw = nullptr;
    }

    VfsFileStreamWriter::~VfsFileStreamWriter()
    {
        delete _fsw;
    }

    void VfsFileStreamWriter::write(const void* data, size_t size)
    {
        _fsw->write(data, size);
    }

    void VfsFileStreamWriter::close()
    {
        _fsw->close();
    }
}
