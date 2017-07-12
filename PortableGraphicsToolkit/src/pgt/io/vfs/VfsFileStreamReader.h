#pragma once
#include <string>
#include <pgt/io/istreams/IStreamReader.h>
namespace pgt {
    class VfsFileStreamReader : public IStreamReader {
        IStreamReader* _fsr;

    public:
        VfsFileStreamReader(const std::string& path);
        ~VfsFileStreamReader();
        VfsFileStreamReader(VfsFileStreamReader&& other);
        bool endOfStream() override;
        size_t read(void* buffer, size_t size) override;
        size_t getPosition() const override;
        size_t getStreamSize() const override;
        size_t readToEnd(void** buffer) override;
        void setPosition(size_t pos) override;
        void close() override;
    };
}