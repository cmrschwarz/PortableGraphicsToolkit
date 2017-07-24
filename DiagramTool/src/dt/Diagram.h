#pragma once
#include <pgt/window/gui/GuiWindow.h>
#include "XAxis.h"
#include "YAxis.h"
#include "Table.h"
typedef const char* str_t;
// str_t xstr, str_t ystr, str_t xval, double yval
typedef void (*CallbackFun)(str_t xstr, str_t ystr, str_t xval, double yval);
namespace dt {
    class Diagram {
        CallbackFun _callback = nullptr;
        pgt::GuiWindow& _window;
        pgt::Font* _font;
        Table& _table;
        double _ymax;
        double _y_lines_stride;
        double _y_lines_value_stride;
        size_t _y_lines_count;
        double _x_stride;
        double _cosy_x, _cosy_y;
        double _cosy_width, _cosy_height;

      public:
        Diagram(pgt::GuiWindow& win, Table& t);
        ~Diagram();
        void setCallback(CallbackFun fun);
        void onClickEvent(pgt::MouseButtonDownEvent& e);
        void onRenderEvent(pgt::Renderer2D& renderer);
        void onResizeEvent(pgt::ResizeEvent w);

      private:
        void measureYAxis();
        static double roundReasonable(double val);
    };
}  // namespace dt