#pragma once
#include "IDirectory.h"
#include "IFile.h"
#include "VDirectory.h"
#include "VfsFileStreamWriter.h"
#include "VfsFileStreamReader.h"
#include "StaticMemoryFile.h"
namespace pgt {
    class VirtualFileSystem {
        friend class VfsFileStreamReader;
        friend class VfsFileStreamWriter;
        VDirectory _root;

    public:
        VirtualFileSystem();
        ~VirtualFileSystem() = default;

    public:
        std::vector<std::string> getAllSubdirectories(const std::string& path);

        std::vector<std::string> getAllFiles(const std::string& path);

        void mountDirectory(const std::string& path, IDirectory& d);

        void addFile(const std::string& path, IFile& f);


    private:
        // TODO: enum the shit out of this to avoid heap alloc. its an
        // implementation detail so who will care / know
        IStreamReader* createFileStreamReader(const std::string& path);

        IStreamWriter* createFileStreamWriter(const std::string& path);
    };
}