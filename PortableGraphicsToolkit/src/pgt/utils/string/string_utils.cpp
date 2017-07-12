#include "string_utils.h"
#include <pgt/maths/maths.h>
#include <pgt/io/logger/logger.h>
#include <cstdarg>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <pgt/utils/string/utf8/utf8.h>
#include <wtypes.h>
#include "string_utf16_back_inserter.h"
namespace pgt {

    const char* getFileNameFromPath(const char* path, int* strlen)
    {
        const char* pos = path;
        const char* pos_after_last_slash = path;
        while (*pos != 0) {
            if (*pos == '/' || *pos == '\\') pos_after_last_slash = pos + 1;
            pos++;
        }
        if (strlen) *strlen = pos - pos_after_last_slash;
        return pos_after_last_slash;
    }
    template <typename Out>
    void split(const std::string& s, char delim, Out result)
    {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string& s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    bool compare_string_case_insensitive(const std::string& str1,
                                         const std::string& str2)
    {
        if (str1.size() != str2.size()) {
            return false;
        }
        for (auto c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end();
             ++c1, ++c2) {
            if (tolower(*c1) != tolower(*c2)) {
                return false;
            }
        }
        return true;
    }

    void string_to_lowercase(std::string& s)
    {
        for (auto it = s.begin(); it != s.end(); ++it) {
            *it = tolower(*it);
        }
    }

    std::string convertUTF16toUTF8(const std::string& w)
    {
        std::string utf8;
        utf8.reserve(w.size() / 2);
        utf8::utf16to8(w.begin(), w.end(), std::back_inserter(utf8));
        return utf8;
    }
    // slightly ineffiecient but who cares
    std::string convertUTF16toUTF8(const char* s)
    {
        std::string utf8;
        const char* se = s;
        while (*se != 0 || *(se + 1) != 0) {
            se += 2;
        }
        utf8.reserve((se - s) / 2);
        utf8::utf16to8((wchar_t*)s, (wchar_t*)se, std::back_inserter(utf8));
        return utf8;
    }

    std::string convertUTF16toUTF8(const WCHAR* s)
    {
        return convertUTF16toUTF8((char*)s);
    }

    std::string convertUTF8toUTF16(const std::string& utf8)
    {
        std::string wstr;
        wstr.reserve(utf8.size() * 2);
        utf8::utf8to16(utf8.begin(), utf8.end(),
                       internal::string_utf16_back_inserter(wstr));
        return wstr;
    }

    std::string convertUTF8toUTF16With00(const std::string& utf8)
    {
        std::string wstr = convertUTF8toUTF16(utf8);
        wstr.push_back('\0');
        wstr.push_back('\0');
        return wstr;
    }

    std::string makeStr(const char* format, ...)
    {
        int size = strlen(format) * 2;  // wild guess
        std::string str;
        va_list ap;
        while (1) {  // Maximum two passes on a POSIX system...
            str.resize(size);
            va_start(ap, format);
            int n = vsnprintf((char*)str.data(), size, format, ap);
            va_end(ap);
            if (n > -1 && n < size) {  // Everything worked
                str.resize(n);
                return str;
            }
            if (n > -1)        // Needed size returned
                size = n + 1;  // For null char
            else
                size *= 2;  // Guess at a larger size (OS specific)
        }
        return str;
    }
}