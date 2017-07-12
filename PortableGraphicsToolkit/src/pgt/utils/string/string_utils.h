#pragma once
#include <string>
#include <vector>

namespace pgt {
    std::string convertUTF16toUTF8(const std::string& w);
    std::string convertUTF16toUTF8(const char* s);
    std::string convertUTF16toUTF8(const wchar_t* s);
    std::string convertUTF8toUTF16(const std::string& utf8);
    std::string convertUTF8toUTF16With00(const std::string& utf8);
    std::string makeStr(const char* types, ...);
    // TODO: make const char* version returning pointer to filename in own str
    const char* getFileNameFromPath(const char* path, int* str_len = nullptr);
    std::vector<std::string> split(const std::string& s, char delim);
    bool compare_string_case_insensitive(const std::string& str1,
                                         const std::string& str2);
    void string_to_lowercase(std::string& s);
}