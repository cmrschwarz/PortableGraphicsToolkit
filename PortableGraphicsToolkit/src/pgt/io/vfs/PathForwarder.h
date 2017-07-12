#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <pgt/utils/string/string_utils.h>
namespace pgt {
    class PathForwarder {
    private:
        std::vector<std::string> _path;
        size_t _curr_child;
        PathForwarder(std::vector<std::string> path, size_t curr_element);

    public:
        PathForwarder(std::string path);
        bool responsible() const;
        bool responsibleForFile() const;
        const std::string& getChild() const;
        std::string getRemainingPath();
        PathForwarder& forward();
    };
}