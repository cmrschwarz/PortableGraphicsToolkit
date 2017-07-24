#include "Table.h"
namespace dt {


    void Table::setValue(size_t x, size_t y, const Content& c)
    {
        // not <= because of xaxis
        for (size_t i = _y_axis.size(); i < x; i++) {
            _y_axis.push_back(YAxis());
        }
        if (x == 0) {
            auto& xax = _x_axis;
            if (y == 0) {
                xax.setName(c.getString());
            }
            else {
                xax.setValue(y - 1, c.getString());
            }
        }
        else {
            auto& column = _y_axis[x - 1];
            if (y == 0) {
                column.setName(c.getString());
            }
            else {
                column.setValue(y - 1, c);
            }
        }
    }

    size_t Table::getYAxisCount() const
    {
        return _y_axis.size();
    }

    dt::XAxis& Table::getXAxis()
    {
        return _x_axis;
    }

    dt::YAxis& Table::getYAxis(size_t id)
    {
        return _y_axis[id];
    }
}
