#pragma once
#include <pgt/io/vfs/IFile.h>
#include <pgt/io/istreams/istreams.h>
#include <pgt/io/memory_streams/MemoryStreamReader.h>
#include <pgt/io/logger/logger.h>
namespace pgt {
    class StaticMemoryFile : public IFile {
    private:
        const unsigned char* _data;
        size_t _size;

    public:
        StaticMemoryFile(const std::string& name, const unsigned char* data,
                         size_t size)
            : IFile(name), _data(data), _size(size)
        {
        }

        virtual IStreamReader* createFileStreamReader() override
        {
            return new MemoryStreamReader(_data, _size);
        }


        virtual IStreamWriter* createFileStreamWriter() override
        {
            PGT_ASSERT(false,
                      "this file is a static part of the exe and cant be "
                      "overwritten");
            return nullptr;
        }
    };
}