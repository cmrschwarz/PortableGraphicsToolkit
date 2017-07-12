#pragma once
#include <vector>
#include <string>
namespace pgt {
    class IFileSystem {
    public:
        virtual std::string getFilepathOfExecutable() = 0;
        virtual std::vector<std::string> getAllFilesWithinFolder(
            const std::string& folder) = 0;
        virtual std::vector<std::string> getAllFoldersWithinFolder(
            const std::string& folder) = 0;
        virtual void createDirectory(const std::string& path) = 0;
        virtual std::string getDesktopPath() = 0;
        virtual void renameFile(const std::string& path,
                                const std::string& name_new) = 0;
        // virtual std::string getAppdataPath();
    };
}