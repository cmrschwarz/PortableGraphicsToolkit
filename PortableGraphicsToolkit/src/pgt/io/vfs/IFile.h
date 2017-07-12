#pragma once
#include <pgt/io/istreams/istreams.h>
#include <pgt/managed_object.h>
namespace pgt {
    class IFile : public IManagedObject {
    private:
        std::string _name;

    public:
        IFile(const std::string& name) : _name(name)
        {
            pgt::string_to_lowercase(_name);
        }
        virtual const std::string& getName()
        {
            return _name;
        }
        virtual void setName(const std::string& s)
        {
            _name = s;
        }
        // user will need to delete, required cause copying is no possible
        virtual IStreamReader* createFileStreamReader() = 0;
        // user will need to delete
        virtual IStreamWriter* createFileStreamWriter() = 0;
        virtual ~IFile(){};

    private:
        IFile(const IFile& r);
    };
}