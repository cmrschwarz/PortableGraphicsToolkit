#pragma once
#include <string>
namespace pgt {
    namespace internal {
        class string_utf16_back_inserter
            : public std::iterator<std::output_iterator_tag, void, void, void,
                                   void> {
        protected:
            std::string* str;

        public:
            typedef std::string container_type;
            string_utf16_back_inserter(std::string& s) : str(&s){};
            string_utf16_back_inserter& operator=(
                const string_utf16_back_inserter& other) = default;
            string_utf16_back_inserter& operator=(wchar_t c)
            {
                str->push_back(((char*)&c)[0]);
                str->push_back(((char*)&c)[1]);
                return *this;
            }
            string_utf16_back_inserter& operator*()
            {
                return *this;
            }
            string_utf16_back_inserter& operator++()
            {
                return *this;
            }
            string_utf16_back_inserter& operator++(int i)
            {
                return *this;
            }
        };
    }
}