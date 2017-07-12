#pragma once
#include <cstddef>
namespace pgt {
    class IStreamReader {
      public:
        virtual bool endOfStream() = 0;
        virtual size_t read(void* buffer, size_t size) = 0;
        virtual size_t getPosition() const = 0;
        virtual void setPosition(size_t pos) = 0;
        virtual size_t getStreamSize() const = 0;
        virtual size_t readToEnd(void** buffer) = 0;
        virtual void close() = 0;
        IStreamReader(){};
        ~IStreamReader(){};

      private:
        IStreamReader(const IStreamReader& r);
    };
}