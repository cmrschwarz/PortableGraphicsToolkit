#include "WindowsFileStreamWriter.h"
#include <pgt/io/logger/logger.h>
namespace pgt {
    namespace plattform {
        WindowsFileStreamWriter::WindowsFileStreamWriter(const std::string path)
        {
            _file = fopen(path.c_str(), "wb+");
        }

        WindowsFileStreamWriter::WindowsFileStreamWriter(
            WindowsFileStreamWriter&& rval)
        {
            _file = rval._file;
            rval._file = nullptr;
        }

        WindowsFileStreamWriter::~WindowsFileStreamWriter()
        {
            if (_file) close();
        }

        void WindowsFileStreamWriter::write(const void* data, size_t size)
        {
            fwrite(data, size, 1, _file);
        }

        void WindowsFileStreamWriter::close()
        {
            fclose(_file);
            _file = nullptr;
        }
    }
}