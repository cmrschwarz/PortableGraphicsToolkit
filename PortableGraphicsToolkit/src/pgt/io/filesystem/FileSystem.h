#pragma once
#include "pgt/io/filesystem/plattform/interface/IFileSystem.h"
#include "pgt/io/filesystem/plattform/target.h"

namespace pgt {
    class FileSystem {
    private:
        static plattform::OSFileSystem _osfs;

    public:
        FileSystem() = delete;
        static std::string getFilepathOfExecutable()
        {
            return _osfs.getFilepathOfExecutable();
        }
        static std::vector<std::string> getAllFilesWithinFolder(
            const std::string& folder)
        {
            return _osfs.getAllFilesWithinFolder(folder);
        }
        static std::vector<std::string> getAllFoldersWithinFolder(
            const std::string& folder)
        {
            return _osfs.getAllFoldersWithinFolder(folder);
        }
        static void createDirectory(const std::string& path)
        {
            return _osfs.createDirectory(path);
        }
        static std::string getDesktopPath()
        {
            return _osfs.getDesktopPath();
        }
        static void renameFile(const std::string& path,
                               const std::string& name_new)
        {
            return _osfs.renameFile(path, name_new);
        }
    };
}
