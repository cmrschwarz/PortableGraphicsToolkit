#include "VDirectory.h"
#include <pgt/io/logger/logger.h>
namespace pgt {

    VDirectory::VDirectory(const std::string& name) : IDirectory(name)
    {
    }

    VDirectory::~VDirectory()
    {
        for (auto it = _directories.begin(); it != _directories.end(); ++it) {
            (*it)->deleteMe();
        }
        for (auto it = _files.begin(); it != _files.end(); ++it) {
            (*it)->deleteMe();
        }
    }

    std::vector<std::string> VDirectory::getAllFiles(PathForwarder& p) const
    {
        if (p.responsible()) {
            std::vector<std::string> v;
            v.reserve(_files.size());
            for (auto it = _files.begin(); it != _files.end(); ++it) {
                v.push_back((*it)->getName());
            }
            return v;
        }
        else {
            return getSubDir(p.getChild())->getAllFiles(p.forward());
        }
    }

    std::vector<std::string> VDirectory::getAllSubdirectories(
        PathForwarder& p) const
    {
        if (p.responsible()) {
            std::vector<std::string> v;
            v.reserve(_directories.size());
            for (auto it = _directories.begin(); it != _directories.end();
                 ++it) {
                v.push_back((*it)->getName());
            }
            return v;
        }
        else {
            return getSubDir(p.getChild())->getAllSubdirectories(p.forward());
        }
    }

    pgt::IStreamReader* VDirectory::createFileStreamReader(
        PathForwarder& p) const
    {
        if (p.responsibleForFile()) {
            return getFile(p.getChild())->createFileStreamReader();
        }
        else {
            return getSubDir(p.getChild())->createFileStreamReader(p.forward());
        }
    }

    inline IStreamWriter* VDirectory::createFileStreamWriter(
        PathForwarder& p) const
    {
        if (p.responsible()) {
            return getFile(p.getChild())->createFileStreamWriter();
        }
        else {
            return getSubDir(p.getChild())->createFileStreamWriter(p.forward());
        }
    }

    inline void VDirectory::mountDirectory(PathForwarder& p, IDirectory& d)
    {
        if (p.responsible()) {
            pushDirectory(d);
        }
        else {
            getSubDir(p.getChild())->mountDirectory(p.forward(), d);
        }
    }

    inline void VDirectory::addFile(PathForwarder& p, IFile& f)
    {
        if (p.responsible()) {
            pushFile(f);
        }
        else {
            getSubDir(p.getChild())->addFile(p.forward(), f);
        }
    }

    inline void VDirectory::pushFile(IFile& f)
    {
        _files.push_back(&f);
    }

    inline void VDirectory::pushDirectory(IDirectory& d)
    {
        _directories.push_back(&d);
    }

    inline void VDirectory::popDirectory(IDirectory& d)
    {
        for (auto it = _directories.begin(); it != _directories.end(); ++it) {
            if (*it == &d) {
                _directories.erase(it);
                return;
            }
        }
        PGT_ASSERT(false,
                  "Directory \"%s\" doesn't exist in vfs Directory \"%s\"",
                  d.getName().c_str(), getName().c_str());
    }

    inline void VDirectory::popFile(IFile& d)
    {
        for (auto it = _files.begin(); it != _files.end(); ++it) {
            if (*it == &d) {
                _files.erase(it);
                return;
            }
        }
        PGT_ASSERT(false, "File \"%s\" doesn't exist in vfs Directory \"%s\"",
                  d.getName().c_str(), getName().c_str());
    }

    inline IDirectory* VDirectory::getSubDir(const std::string& name) const
    {
        for (auto it = _directories.begin(); it != _directories.end(); ++it) {
            if ((*it)->getName() == name) return *it;
        }
        PGT_ASSERT(false,
                  "Directory \"%s\" doesn't exist in vfs Directory \"%s\"",
                  name.c_str(), getName().c_str());
    }

    inline IFile* VDirectory::getFile(const std::string& name) const
    {
        for (auto it = _files.begin(); it != _files.end(); ++it) {
            if ((*it)->getName() == name) return *it;
        }
        PGT_ASSERT(false, "File \"%s\" doesn't exist in vfs Directory \"%s\"",
                  name.c_str(), getName().c_str());
    }
}
