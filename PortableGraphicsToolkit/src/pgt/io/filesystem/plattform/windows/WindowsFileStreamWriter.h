#pragma once
#include <pgt/io/istreams/IStreamWriter.h>
#include <string>
namespace pgt {
    namespace plattform {
        class WindowsFileStreamWriter : public IStreamWriter {
        private:
            FILE* _file;

        public:
            WindowsFileStreamWriter(const std::string path);
            WindowsFileStreamWriter(WindowsFileStreamWriter&& rval);
            ~WindowsFileStreamWriter();
            virtual void write(const void* data, size_t size) override;
            virtual void close() override;
        };
    }
}