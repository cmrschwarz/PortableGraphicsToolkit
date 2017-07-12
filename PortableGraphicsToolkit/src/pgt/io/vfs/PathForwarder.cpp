#include "PathForwarder.h"
#include <pgt/io/vfs/VirtualFileSystem.h>
#include <pgt/io/filesystem/filesystem.h>
#include <pgt/utils/string/path_utils.h>
namespace pgt {
    PathForwarder::PathForwarder(std::vector<std::string> path,
                                 size_t curr_element)
        : _path(path), _curr_child(curr_element)
    {
    }
    PathForwarder::PathForwarder(std::string path)
    {
        sanitizePathName(path);
        _path = pgt::split(path, '/');
        _curr_child = 0;  // we have a root
    }
    bool PathForwarder::responsible() const
    {
        return (_path.size() - 1 == _curr_child);
    }
    bool PathForwarder::responsibleForFile() const
    {
        return (_path.size() - 1 == _curr_child + 1);
    }
    const std::string& PathForwarder::getChild() const
    {
        return _path[_curr_child + 1];
    }
    std::string PathForwarder::getRemainingPath()
    {
        std::string ret;
        for (size_t i = _curr_child +1 ; i < _path.size(); i++) {
            if (i > _curr_child+1) ret += '/';
            ret += _path[i];
        }
        return ret;
    }
    PathForwarder& PathForwarder::forward()
    {
        _curr_child++;
        return *this;
    }
}
