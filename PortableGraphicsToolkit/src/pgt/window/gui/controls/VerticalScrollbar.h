#pragma once
#include "RectangularControl.h"
namespace pgt {
    // TODO: maybe add arrows indicating the scrollbars
    class VerticalScrollbar : public RectangularControl {
    private:
        int _dragged_y = -1;  // x=-1 means not dragged; -2 means not touched
        int _max_scroll = 100;
        int _scroll_value = 0;
        float _bar_percentage = 0.2f;
        Rectangle _bar;
        static const int _border_width = 3;

    public:
        VerticalScrollbar();

    public:
        void onResize(ResizeEvent& e) override;
        void onRender(Render2DEvent& e) override;
        void onMouseButtonDown(MouseButtonDownEvent& e) override;
        void onMouseButtonUp(MouseButtonUpEvent& e) override;
        void onMouseMoved(MouseMoveEvent& e) override;
        void onMouseScrolled(MouseScrollEvent& e) override;
        void setMaxScroll(int max);
        void setBarPercentage(float bar_percentage);
        int getValue() const;
        void setValue(int val);

    private:
        void updateBarBounds();
        void updateBarPos();
        void updateScrollValue();
        int clampBarPos(int pos_y);
    };
}