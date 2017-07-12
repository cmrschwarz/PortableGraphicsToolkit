#include "VfsFileStreamReader.h"
#include "VirtualFileSystem.h"
#include <pgt/window/engine.h>
namespace pgt {

    VfsFileStreamReader::VfsFileStreamReader(VfsFileStreamReader&& other)
    {
        _fsr = other._fsr;
        other._fsr = nullptr;
    }

    VfsFileStreamReader::VfsFileStreamReader(const std::string& path)
        : _fsr(engine::getApp().getVFS().createFileStreamReader(path))
    {
    }

    VfsFileStreamReader::~VfsFileStreamReader()
    {
        delete _fsr;
    }

    bool VfsFileStreamReader::endOfStream()
    {
        return _fsr->endOfStream();
    }
    size_t VfsFileStreamReader::read(void* buffer, size_t size)
    {
        return _fsr->read(buffer, size);
    }
    size_t VfsFileStreamReader::getPosition() const
    {
        return _fsr->getPosition();
    }
    size_t VfsFileStreamReader::getStreamSize() const
    {
        return _fsr->getStreamSize();
    }
    size_t VfsFileStreamReader::readToEnd(void** buffer)
    {
        return _fsr->readToEnd(buffer);
    }
    void VfsFileStreamReader::setPosition(size_t pos)
    {
        _fsr->setPosition(pos);
    }
    void VfsFileStreamReader::close()
    {
        _fsr->close();
    }
}
