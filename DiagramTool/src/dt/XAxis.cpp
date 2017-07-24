#include "XAxis.h"

namespace dt {

    XAxis::XAxis()
    {
    }

    XAxis::XAxis(const std::vector<Content>& content)
    {
        auto it = content.begin();
        _name = (*it).getString();
        _data.reserve(content.size() - 1);
        for (++it; it != content.end(); ++it) {
            _data.push_back((*it).getString());
        }
    }

    const std::string& XAxis::getName()
    {
        return _name;
    }

    void XAxis::setName(const std::string& name)
    {
        _name = name;
    }

    void XAxis::setValue(uint32_t pos, const std::string& value)
    {
        std::string str("");
        while (_data.size() <= pos) {
            _data.push_back(str);
        }
        _data[pos] = value;
    }

    const std::string& XAxis::getValue(uint32_t pos)
    {
        return _data[pos];
    }

    uint32_t XAxis::getSize()
    {
        return _data.size();
    }
}