#pragma once
#include <string>
#include "Content.h"
#include <pgt/maths/maths.h>
#include <pgt/graphics/Color.h>
namespace dt {
    enum class DisplayType {
        BARS,
        LINE,
    };
    struct YVal {
        pgt::vec2i pos;
        pgt::vec2i size;
        Content content;
    };
    class YAxis {
        DisplayType _display_type;
        std::string _name;
        std::vector<YVal> _data;
        double _min_val;
        double _max_val;
        pgt::Color _color;

      public:
        YAxis();

      public:
        DisplayType getDisplayType();
        void setDisplayType(DisplayType dp);
        const std::string& getName();
        void setName(const std::string& name);
        void setValue(size_t pos, const Content& c);
        const Content& getValue(size_t id);
        const pgt::vec2i& getPos(size_t id);

        void setPos(size_t id, const pgt::vec2i& pos);
        void setSize(size_t id, const pgt::vec2i& pos);
        uint32_t getSize();
        const pgt::vec2i& getSize(size_t id);
        void calculateMetrics();  // ugly but works
        double getMinVal();
        double getMaxVal();
        void setColor(pgt::Color c);
        pgt::Color getColor();
    };
}