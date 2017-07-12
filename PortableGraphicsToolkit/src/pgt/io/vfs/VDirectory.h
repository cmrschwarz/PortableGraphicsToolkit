#pragma once
#include "IDirectory.h"
#include "IFile.h"
namespace pgt {
    class VDirectory : public IDirectory {
    private:
        std::vector<IFile*> _files;
        std::vector<IDirectory*> _directories;

    public:
        VDirectory(const std::string& name);
        ;
        ~VDirectory();

    public:
        std::vector<std::string> getAllFiles(PathForwarder& p) const override;

        std::vector<std::string> getAllSubdirectories(
            PathForwarder& p) const override;
        virtual IStreamReader* createFileStreamReader(
            PathForwarder& p) const override;

        virtual IStreamWriter* createFileStreamWriter(
            PathForwarder& p) const override;

        virtual void mountDirectory(PathForwarder& p, IDirectory& d) override;
        virtual void addFile(PathForwarder& p, IFile& f) override;

    private:
        void pushFile(IFile& f);
        void pushDirectory(IDirectory& d);
        void popDirectory(IDirectory& d);
        void popFile(IFile& d);

    private:
        IDirectory* getSubDir(const std::string& name) const;
        IFile* getFile(const std::string& name) const;
    };
}