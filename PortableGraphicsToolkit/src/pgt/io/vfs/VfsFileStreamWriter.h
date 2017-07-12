#pragma once
#include <string>
#include <pgt/io/istreams/IStreamWriter.h>
namespace pgt {
    class VDirectory;
    class VfsFileStreamWriter : public IStreamWriter {
        IStreamWriter* _fsw;

    public:
        VfsFileStreamWriter(const std::string& path);
        VfsFileStreamWriter(VfsFileStreamWriter&& other);
        ~VfsFileStreamWriter() override;
        void write(const void* data, size_t size) override;
        void close() override;
    };
}