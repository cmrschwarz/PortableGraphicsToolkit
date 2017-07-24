#include "Diagram.h"
#include <float.h>
#include <pgt/utils/debug/MessageBoxes.h>
namespace dt {

    Diagram::Diagram(pgt::GuiWindow& win, Table& table)
        : _window(win), _table(table)

    {
        win.getRenderingContext().getFontManager().submitFont(pgt::Font(
            "ArialRoundedMT", 12,
            (pgt::VfsFileStreamReader("/res/fonts/arialroundedmt.ttf"))));
        _font = new pgt::Font("ArialRoundedMT", 12);
        measureYAxis();
    }


    Diagram::~Diagram()
    {
        delete _font;
    }

    void Diagram::measureYAxis()
    {
        _ymax = DBL_MIN;
        double yacc;
        for (size_t i = 0; i < _table.getXAxis().getSize(); i++) {
            yacc = 0;
            for (size_t c = 0; c < _table.getYAxisCount(); c++) {
                auto& cont = _table.getYAxis(c).getValue(i);
                if (!cont.isDouble()) continue;
                double val = cont.getDouble();
                if (_table.getYAxis(c).getDisplayType() != DisplayType::BARS) {
                    if (val > _ymax) _ymax = val;
                }
                else {
                    yacc += val;
                }
            }
            if (yacc > _ymax) _ymax = yacc;
        }
        _ymax = roundReasonable(_ymax);
        _y_lines_count = 10;
        _y_lines_value_stride = roundReasonable(_ymax / (_y_lines_count));
        while ((_y_lines_count - 1) * _y_lines_value_stride > _ymax) {
            _y_lines_count--;
        }
        if (_y_lines_count * _y_lines_value_stride >= _ymax)
            _ymax += _y_lines_value_stride;
    }
    double Diagram::roundReasonable(double val)
    {
        double sign = val > 0 ? 1 : -1;
        val = std::abs(val);
        static const double units[]{1.0, 5, 20, 200, 500, 1000};
        size_t digits = 1;
        size_t i = 1;
        while (val / (std::pow(10, i)) > 1) {
            digits++;
            i++;
        }
        double unit = units[pgt::min(digits - 1, 5U)];
        double rem = val - std::floor(val / unit) * unit;
        if (rem > 0) rem = unit - rem;
        return (val + rem) * sign;
    }

    void Diagram::setCallback(CallbackFun fun)
    {
        _callback = fun;
    }

    void Diagram::onClickEvent(pgt::MouseButtonDownEvent& e)
    {
        if (_callback == nullptr) return;
        for (size_t i = 0; i < _table.getXAxis().getSize(); i++) {
            for (size_t c = 0; c < _table.getYAxisCount(); c++) {
                const pgt::vec2i& pos = _table.getYAxis(c).getPos(i);
                const pgt::vec2i& size = _table.getYAxis(c).getSize(i);
                if (e.x >= pos.x && e.x <= pos.x + size.x && e.y >= pos.y &&
                    e.y <= pos.y + size.y) {
                    str_t xnam = _table.getXAxis().getName().c_str();
                    str_t xval = _table.getXAxis().getValue(i).c_str();
                    str_t ynam = _table.getYAxis(c).getName().c_str();
                    double yval = _table.getYAxis(c).getValue(i).getDouble();
                    // xnam, xval, ynam, yval
                    (*_callback)(xnam, xval, ynam, yval);
                    return;
                }
            }
        }
    }
    void Diagram::onResizeEvent(pgt::ResizeEvent w)
    {
    }
    void Diagram::onRenderEvent(pgt::Renderer2D& renderer)
    {
        // background
        using namespace pgt;
        Rectangle bounds =
            _window.getViewport();  //_window.getPanel().getBounds();
        renderer.setColor(0xFFFFFFFF);
        renderer.fillRectangle(bounds.pos, bounds.size);
        renderer.setFont(*_font);
        float line_th = 2;
        // cosy+pos
        float margin = 30;
        float line_b = 10;
        _cosy_x =
            renderer.getFont().measureString(pgt::makeStr("%.2f", _ymax)).x +
            line_b + 3;
        _cosy_y = bounds.size.y - margin;
        _cosy_width = bounds.size.x - _cosy_x - margin;
        _cosy_height = bounds.size.y - margin * 2;
        _x_stride = _cosy_width / (_table.getXAxis().getSize() + 1);
        renderer.setColor(Color::BLACK);
        renderer.drawLine(vec2i(_cosy_x, _cosy_y),
                          vec2i(_cosy_x + _cosy_width, _cosy_y), line_th);
        renderer.drawLine(vec2i(_cosy_x, _cosy_y),
                          vec2i(_cosy_x, _cosy_y - _cosy_height), line_th);
        vec3i sb =
            renderer.getFont().measureString(_table.getXAxis().getName());
        renderer.drawString(
            _table.getXAxis().getName(),
            vec2i(_cosy_x + _cosy_width - sb.x / 1.5, _cosy_y - sb.z + 2));
        // x axis

        for (size_t i = 0; i < _table.getXAxis().getSize(); i++) {
            float x = _cosy_x + (i + 1) * _x_stride;
            renderer.drawLine(vec2i(x, _cosy_y - line_b),
                              vec2i(x, _cosy_y + line_b), line_th);
            vec3i s =
                renderer.getFont().measureString(_table.getXAxis().getValue(i));
            renderer.drawString(_table.getXAxis().getValue(i),
                                vec2i(x - s.x / 2, _cosy_y + line_b));
        }
        float last_line_value_per =
            ((_y_lines_count * _y_lines_value_stride) / _ymax) * _cosy_height;
        _y_lines_stride = last_line_value_per / _y_lines_count;

        // y axis
        for (size_t i = 0; i < _y_lines_count; i++) {
            float y = _cosy_y - (i + 1) * _y_lines_stride;
            renderer.drawLine(vec2i(_cosy_x - line_b, y),
                              vec2i(_cosy_x + line_b, y), line_th);
            std::string numstr =
                pgt::makeStr("%.2f", (i + 1) * _y_lines_value_stride);
            vec3i s = renderer.getFont().measureString(numstr);
            renderer.drawString(
                numstr, vec2i(_cosy_x - s.x - line_b - 2, y - (s.y + s.z) / 2));
        }
        // bars
        float bar_b = _x_stride / 4;
        std::vector<std::pair<double, size_t>> vals;
        for (size_t i = 0; i < _table.getXAxis().getSize(); i++) {
            float hused = line_th / 2;
            for (size_t c = 0; c < _table.getYAxisCount(); c++) {
                if ((_table.getYAxis(c).getDisplayType() != DisplayType::BARS ||
                     _table.getYAxis(c).getValue(i).isDouble() == false))
                    continue;
                double val = _table.getYAxis(c).getValue(i).getDouble();


                vec2i bpos(_cosy_x + (i + 1) * _x_stride - bar_b,
                           _cosy_y - ((val / _ymax) * _cosy_height) - hused);
                vec2i bsize(bar_b * 2, _cosy_y - bpos.y - hused);
                _table.getYAxis(c).setPos(i, bpos);
                _table.getYAxis(c).setSize(i, bsize);
                hused = _cosy_y - bpos.y;
                renderer.setColor(_table.getYAxis(c).getColor());
                renderer.fillRectangle(bpos, bsize);
            }
        }
        for (size_t c = 0; c < _table.getYAxisCount(); c++) {
            auto& yax = _table.getYAxis(c);
            if (yax.getDisplayType() != DisplayType::LINE) continue;
            renderer.setColor(_table.getYAxis(c).getColor());
            vec2i last;
            for (size_t i = 0; i < _table.getYAxis(c).getSize(); i++) {
                if (!yax.getValue(i).isDouble()) continue;
                vec2i curr(_cosy_x + (i + 1) * _x_stride,
                           _cosy_y - ((yax.getValue(i).getDouble() / _ymax) *
                                      _cosy_height));

                if (last.x != 0) {
                    renderer.drawLine(last, curr, line_th * 2);
                }
                last = curr;
            }
        }
    }
}  // namespace dt