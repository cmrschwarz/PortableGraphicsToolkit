#pragma once
#include <pgt/io/istreams/istreams.h>
#include "PathForwarder.h"
#include <pgt/managed_object.h>
#include <vector>
namespace pgt {
    class IFile;
    class IDirectory : public IManagedObject {
    private:
        std::string _name;

    public:
        IDirectory(const std::string& name) : _name(name)
        {
        }
        virtual ~IDirectory(){};
        virtual const std::string& getName() const
        {
            return _name;
        }
        virtual void setName(const std::string& s)
        {
            _name = s;
        }
        virtual std::vector<std::string> getAllSubdirectories(
            PathForwarder& p) const = 0;
        virtual std::vector<std::string> getAllFiles(
            PathForwarder& p) const = 0;

        virtual IStreamReader* createFileStreamReader(
            PathForwarder& p) const = 0;

        virtual IStreamWriter* createFileStreamWriter(
            PathForwarder& p) const = 0;

        virtual void mountDirectory(PathForwarder& p, IDirectory& d) = 0;
        virtual void addFile(PathForwarder& p, IFile& f) = 0;

    private:
        IDirectory(const IDirectory& d);
    };
}