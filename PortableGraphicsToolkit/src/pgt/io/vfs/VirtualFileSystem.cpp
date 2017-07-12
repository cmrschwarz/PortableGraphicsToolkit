#include "VirtualFileSystem.h"

namespace pgt {



    VirtualFileSystem::VirtualFileSystem() : _root("/")
    {
    }

    std::vector<std::string> VirtualFileSystem::getAllSubdirectories(
        const std::string& path)
    {
        PathForwarder p(path);
        return _root.getAllSubdirectories(p);
    }

    std::vector<std::string> VirtualFileSystem::getAllFiles(
        const std::string& path)
    {
        PathForwarder p (path);
        return _root.getAllFiles(p);
    }

    void VirtualFileSystem::mountDirectory(const std::string& path,
                                           IDirectory& d)
    {
        PathForwarder p (path);
        _root.mountDirectory(p, d);
    }

    void VirtualFileSystem::addFile(const std::string& path, IFile& f)
    {
        PathForwarder p(path);
        _root.addFile(p, f);
    }

    pgt::IStreamReader* VirtualFileSystem::createFileStreamReader(
        const std::string& path)
    {
        PathForwarder p(path);
        return _root.createFileStreamReader(p);
    }

    pgt::IStreamWriter* VirtualFileSystem::createFileStreamWriter(
        const std::string& path)
    {
        PathForwarder p(path);
        return _root.createFileStreamWriter(p);
    }
}
