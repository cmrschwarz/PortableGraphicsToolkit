#include "YAxis.h"
#include <assert.h>
namespace dt {
    YAxis::YAxis()
    {
        _display_type = DisplayType::BARS;
        _color = pgt::Color::randomColor();
    }

    dt::DisplayType YAxis::getDisplayType()
    {
        return _display_type;
    }

    void YAxis::setDisplayType(DisplayType dp)
    {
        _display_type = dp;
    }

    const std::string& YAxis::getName()
    {
        return _name;
    }

    void YAxis::setName(const std::string& name)
    {
        _name = name;
    }

    void YAxis::setValue(size_t pos, const Content& value)
    {
        YVal val;
        while (_data.size() <= pos) {
            _data.push_back(val);
        }
        _data[pos].content = value;
    }

    const Content& YAxis::getValue(size_t pos)
    {
        return _data[pos].content;
    }

    const pgt::vec2i& YAxis::getPos(size_t pos)
    {
        return _data[pos].pos;
    }
    const pgt::vec2i& YAxis::getSize(uint32_t pos)
    {
        return _data[pos].size;
    }


    uint32_t YAxis::getSize()
    {
        return _data.size();
    }

    void YAxis::setPos(size_t id, const pgt::vec2i& pos)
    {
        _data[id].pos = pos;
    }

    void YAxis::setSize(size_t id, const pgt::vec2i& size)
    {
        _data[id].size = size;
    }

    void YAxis::calculateMetrics()
    {
        _min_val = DBL_MAX;
        _max_val = DBL_MIN;
        for (auto it = _data.begin(); it != _data.end(); ++it) {
            if (!(*it).content.isDouble()) continue;
            double val = (*it).content.getDouble();
            if (val < _min_val) _min_val = val;
            if (val > _max_val) _max_val = val;
        }
        if (_max_val == DBL_MIN && _min_val == DBL_MAX) {
            _max_val = 0;
            _min_val = 0;
        }
    }

    double YAxis::getMinVal()
    {
        return _min_val;
    }

    double YAxis::getMaxVal()
    {
        return _max_val;
    }

    void YAxis::setColor(pgt::Color c)
    {
        _color = c;
    }

    pgt::Color YAxis::getColor()
    {
        return _color;
    }
}