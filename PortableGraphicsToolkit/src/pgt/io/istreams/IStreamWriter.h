#pragma once
#include <pgt/utils/std_types.h>
namespace pgt {
    class IStreamWriter {
    public:
        virtual void write(const void* data, size_t size) = 0;
        virtual void close() = 0;
        IStreamWriter(){};
        virtual ~IStreamWriter(){};

    private:
        IStreamWriter(const IStreamWriter& r);
    };
}