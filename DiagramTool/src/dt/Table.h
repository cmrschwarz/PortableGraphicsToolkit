#pragma once
#include "Content.h"
#include "XAxis.h"
#include "YAxis.h"
namespace dt {

    class Table {
        std::vector<YAxis> _y_axis;
        XAxis _x_axis;
        static Content EMPTY_CONTENT;

      public:
        Table(){};
        ~Table(){};

      public:
        void setValue(size_t x, size_t y, const Content& c);
        size_t getYAxisCount() const;
        XAxis& getXAxis();
        YAxis& getYAxis(size_t id);
    };
}