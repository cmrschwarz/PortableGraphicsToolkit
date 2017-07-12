#pragma once
#include <pgt/io/filesystem/plattform/interface/IFilesystem.h>
namespace pgt {
    namespace plattform {
        class FileSystemWindows final : public IFileSystem {
        public:
            std::string getFilepathOfExecutable() override;
            std::vector<std::string> getAllFilesWithinFolder(
                const std::string& folder) override;
            std::vector<std::string> getAllFoldersWithinFolder(
                const std::string& folder) override;
            void createDirectory(const std::string& path) override;
            std::string getDesktopPath() override;
            void renameFile(const std::string& path,
                            const std::string& name_new) override;
        };
    }
}