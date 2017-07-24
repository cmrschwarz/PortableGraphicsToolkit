#pragma once
#include <string>
#include "Content.h"
namespace dt {
    class XAxis {
        std::string _name;
        std::vector<std::string> _data;

      public:
        XAxis(const std::vector<Content>& content);
        XAxis();

      public:
        const std::string& getName();
        void setName(const std::string& name);
        void setValue(uint32_t pos, const std::string& str);
        const std::string& getValue(uint32_t pos);
        uint32_t getSize();
    };
}