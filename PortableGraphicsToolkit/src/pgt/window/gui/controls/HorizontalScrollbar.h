#pragma once
#include "RectangularControl.h"
namespace pgt {
    class HorizontalScrollbar : public RectangularControl {
      private:
        int _dragged_x = -1;  // x=-1 means not dragged
        int _max_scroll = 100;
        int _scroll_value = 0;
        float _bar_percentage = 0.2f;
        Rectangle _bar;
        static const int _border_width = 3;

      public:
        HorizontalScrollbar();

      public:
        void onResize(ResizeEvent& e) override;
        void onRender(Render2DEvent& e) override;
        void onMouseButtonDown(MouseButtonDownEvent& e) override;
        void onMouseButtonUp(MouseButtonUpEvent& e) override;
        void onMouseMoved(MouseMoveEvent& e) override;
        void onMouseScrolled(MouseScrollEvent& e) override;
        void setMaxScroll(int max);
        void setBarPercentage(float bar_percentage);
        int getValue();
        void setValue(int val);

      private:
        void updateBarBounds();
        void updateBarPos();
        void updateScrollValue();
        int clampBarPos(int pos_y);
    };
}