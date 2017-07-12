#pragma once
#include <pgt/io/vfs/IFile.h>
#include <pgt/io/memory_streams/MemoryStreamReader.h>
#include <pgt/io/memory_streams/MemoryStreamWriter.h>
#include <pgt/io/istreams/istreams.h>
namespace pgt {
    class DynamicMemoryFile : public IFile {
    private:
        unsigned char* _data;
        size_t _size;

    public:
        DynamicMemoryFile(const std::string& name, unsigned char* data,
                          size_t size)
            : IFile(name), _data(data), _size(size)
        {
        }
        ~DynamicMemoryFile()
        {
            delete[] _data;
        }

    public:
        virtual IStreamReader* createFileStreamReader() override
        {
            return new MemoryStreamReader(_data, _size);
        }


        virtual IStreamWriter* createFileStreamWriter() override
        {
            return new MemoryStreamWriter(&_data, _size);
        }
    };
}