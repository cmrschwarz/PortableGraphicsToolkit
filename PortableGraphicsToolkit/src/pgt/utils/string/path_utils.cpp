#include "path_utils.h"
#include <algorithm>


namespace pgt {
    void sanitizePathName(std::string& path)
    {
        std::replace(path.begin(), path.end(), '\\', '/');
        if (path[path.length() - 1] == '/' && path.length()>1) path.pop_back();
     
    }
}