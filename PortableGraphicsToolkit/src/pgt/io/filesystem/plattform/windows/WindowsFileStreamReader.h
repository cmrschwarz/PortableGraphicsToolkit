#pragma once
#include <pgt/io/istreams/IStreamReader.h>
#include <pgt/io/logger/logger.h>
#include <string>
#include <stdio.h>
#include <vector>
namespace pgt {
    namespace plattform {
        class WindowsFileStreamReader : public IStreamReader {
        private:
            FILE* _file;
            size_t _streampos;

        public:
            WindowsFileStreamReader(const std::string& file);
            WindowsFileStreamReader(WindowsFileStreamReader&& rval);
            ~WindowsFileStreamReader();

        public:
            virtual bool endOfStream() override;
            virtual size_t read(void* buffer, size_t size) override;
            virtual size_t getPosition() const override;
            virtual size_t getStreamSize() const override;
            virtual size_t readToEnd(void** buffer) override;
            virtual void setPosition(size_t pos) override;
            virtual void close() override;
        };
    }
}