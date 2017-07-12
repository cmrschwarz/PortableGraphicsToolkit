#include "OSDirectory.h"
#include <windows.h>
#include <pgt/io/filesystem/Filesystem.h>
#include <pgt/io/istreams/istreams.h>
#include <pgt/utils/string/path_utils.h>
namespace pgt {
    OSDirectory::OSDirectory(const std::string& name,
                             const std::string& os_path)
        : IDirectory(name)
    {
        _os_path = os_path;
        sanitizePathName(_os_path);
        _os_path.push_back('/');
    }

    std::vector<std::string> OSDirectory::getAllSubdirectories(
        PathForwarder& p) const
    {
        return FileSystem::getAllFoldersWithinFolder(_os_path +
                                                     p.getRemainingPath());
    }

    std::vector<std::string> OSDirectory::getAllFiles(PathForwarder& p) const
    {
        return FileSystem::getAllFilesWithinFolder(_os_path +
                                                   p.getRemainingPath());
    }

    pgt::IStreamReader* OSDirectory::createFileStreamReader(
        PathForwarder& p) const
    {
        return new FileStreamReader(_os_path + p.getRemainingPath());
    }

    pgt::IStreamWriter* OSDirectory::createFileStreamWriter(
        PathForwarder& p) const
    {
        return new FileStreamWriter(_os_path + p.getRemainingPath());
    }

    void OSDirectory::mountDirectory(PathForwarder& p, IDirectory& d)
    {
        PGT_ASSERT(false, "cant mout into real os directory");
    }

    void OSDirectory::addFile(PathForwarder& p, IFile& f)
    {
        PGT_ASSERT(false, "cant mout into real os directory");
    }
}
