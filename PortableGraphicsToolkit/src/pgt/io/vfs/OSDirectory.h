#pragma once
#include <pgt/io/vfs/IDirectory.h>
namespace pgt {
    class OSDirectory : public IDirectory {
    private:
        std::string _os_path;

    public:
        OSDirectory(const std::string& name, const std::string& os_path);

        virtual std::vector<std::string> getAllSubdirectories(
            PathForwarder& p) const override;


        virtual std::vector<std::string> getAllFiles(
            PathForwarder& p) const override;


        virtual IStreamReader* createFileStreamReader(
            PathForwarder& p) const override;


        virtual IStreamWriter* createFileStreamWriter(
            PathForwarder& p) const override;


        virtual void mountDirectory(PathForwarder& p, IDirectory& d) override;


        virtual void addFile(PathForwarder& p, IFile& f) override;
    };
}