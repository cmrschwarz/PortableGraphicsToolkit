#include "WindowsFileStreamReader.h"

namespace pgt {
    namespace plattform {
        WindowsFileStreamReader::WindowsFileStreamReader(
            const std::string& file)
        {
            _file = fopen(file.c_str(), "rb");
            PGT_ASSERT(_file, "Failed to open File \"%s\"", file.c_str());
            _streampos = 0;
        }

        WindowsFileStreamReader::WindowsFileStreamReader(
            WindowsFileStreamReader&& rval)
        {
            _file = rval._file;
            _streampos = rval._streampos;
            rval._file = nullptr;
        }

        WindowsFileStreamReader::~WindowsFileStreamReader()
        {
            if (_file) fclose(_file);
        }

        bool WindowsFileStreamReader::endOfStream()
        {
            return feof(_file) == 1;
        }

        size_t WindowsFileStreamReader::read(void* buffer, size_t size)
        {
            size_t rval = fread(buffer, size, 1, _file);
            if (rval == 1) {
                _streampos += size;
                rval = size;
            }
            else {
                size_t eof_pos = ftell(_file);
                rval = eof_pos - _streampos;  //-1??
                _streampos = eof_pos;
            }
            return rval;
        }

        size_t WindowsFileStreamReader::getPosition() const
        {
            return _streampos;
        }

        size_t WindowsFileStreamReader::getStreamSize() const
        {
            int res = fseek(_file, 0, SEEK_END);
            PGT_DEBUG_ASSERT(res == 0, "Your Plattform doesnt support this");
            size_t ret_val = ftell(_file);
            fseek(_file, _streampos, SEEK_SET);
            return ret_val;
        }

        size_t WindowsFileStreamReader::readToEnd(void** buffer)
        {
            const size_t BSIZE = 1024;
            std::vector<void*> _buffers;
            size_t r;
            while (true) {
                void* buffer = malloc(BSIZE);
                r = fread(buffer, BSIZE, 1, _file);
                _buffers.push_back(buffer);
                if (r == 0) break;
            }
            size_t buffer_size = ftell(_file) - _streampos;
            size_t last_buffer_size =
                buffer_size - (_buffers.size() - 1) * BSIZE;
            typedef uint8_t byte_t;
            uint8_t** b_ptr = reinterpret_cast<uint8_t**>(buffer);
            *b_ptr = new byte_t[buffer_size];
            // memcpy protects against 0 case
            byte_t* buff_pos = *b_ptr;
            for (auto it = _buffers.begin(); it != _buffers.end() - 1; ++it) {
                memcpy(buff_pos, *it, BSIZE);
                buff_pos += BSIZE;
                free(*it);
            }
            memcpy(buff_pos, _buffers.back(), last_buffer_size);
            free(_buffers.back());
            _streampos += buffer_size;
            return buffer_size;
        }
        void WindowsFileStreamReader::freeReadToEndBuffer(void* buffer)const {
            delete[] (uint8_t*)buffer;
        }
        void WindowsFileStreamReader::setPosition(size_t pos)
        {
            _streampos = pos;
            int res = fseek(_file, pos, SEEK_SET);
            PGT_DEBUG_ASSERT(res == 0,
                            "File read access violation: index out of bounds");
        }

        void WindowsFileStreamReader::close()
        {
            fclose(_file);
            _file = nullptr;
        }
    }
}