#pragma once
#include <pgt/io/streams/IStreamWriter.h>
#include <stdexcept>
#include <pgt/io/logger/logger.h>

namespace pgt {
    class MemoryStreamWriter : public IStreamWriter {
    private:
        unsigned char** _data;
        size_t _size;

    public:
        MemoryStreamWriter(unsigned char** data, size_t size)
            : _data(data), _size(size)
        {
        }
        MemoryStreamWriter(MemoryStreamWriter&& rval)
        {
            _data = rval._data;
            _size = rval._size;
            rval._data = nullptr;
        }

    public:
        virtual void write(const void* data, size_t size) override
        {
            PGT_ASSERT(false, "Cannot write to static memory");
        }


        virtual void close() override
        {
        }
    };
}
