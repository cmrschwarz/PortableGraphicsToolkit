#pragma once
#include <pgt/io/istreams/IStreamReader.h>
#include <stdexcept>
namespace pgt {
    class MemoryStreamReader : public IStreamReader {
    private:
        const unsigned char* _data;
        const unsigned char* _position;
        const unsigned char* _end;

    public:
        MemoryStreamReader(const unsigned char* data, size_t size)
            : _data(data), _position(data), _end(data + size)
        {
        }
        MemoryStreamReader(MemoryStreamReader&& rval)
        {
            _data = rval._data;
            _position = rval._position;
            _end = rval._end;
            rval._data = nullptr;
        }

    public:
        bool endOfStream() override
        {
            return (_position >= _end);
        }


        size_t read(void* buffer, size_t size) override
        {
            size_t fsize_left = _end - _position;
            if (fsize_left > size) {
                memcpy(buffer, _position, size);
                _position += size;
                return size;
            }
            else {
                memcpy(buffer, _position, fsize_left);
                _position = _end;
                return fsize_left;
            }
        }


        size_t getPosition() const override
        {
            return _position - _data;
        }


        size_t getStreamSize() const override
        {
            return _end - _data;  // THIS IS DIFFERENT
        }


        size_t readToEnd(void** buffer) override
        {
            size_t fsize_left = _end - _position;
            *buffer = malloc(fsize_left);
            return read(*buffer, fsize_left);
        }


        void setPosition(size_t pos) override
        {
            _position = _data + pos;
        }


        void close() override
        {
        }
    };
}