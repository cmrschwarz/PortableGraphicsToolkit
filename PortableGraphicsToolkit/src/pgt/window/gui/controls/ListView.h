#pragma once
#include <pgt/window/gui/GuiComponent.h>
#include "HorizontalScrollbar.h"
#include "VerticalScrollbar.h"
#include <pgt/window/gui/GuiComponentContainer.h>
#include "RectangularControl.h"
#include "ListViewItem.h"
namespace pgt {

    class ListView
        : public GuiComponentContainer<RectangularControl, ListViewItem> {
    public:
        enum ScrollbarVisibility {
            ALWAYS_VISIBLE,
            AS_NEEDED,
            ALWAYS_HIDDEN,
        };

    private:
        int _item_height = 40;
        int _item_width = -1;
        ScrollbarVisibility _vertical_scrollbar_visibility = AS_NEEDED;
        ScrollbarVisibility _horizontal_scrollbar_visibility = AS_NEEDED;
        HorizontalScrollbar* _horizontal_scrollbar;
        VerticalScrollbar* _vertical_scrollbar;

    public:
        ListView();
        ~ListView();
        void addItem(ListViewItem& it);
        ListViewItem& getItem(int index);
        void setItem(int index, ListViewItem& it);
        void removeItem(int index);
        void clear();

    public:
        void setHorizontalScrollbarVisibility(ScrollbarVisibility sbv);
        void setVerticalScrollbarVisibility(ScrollbarVisibility sbv);
        void setItemWidth(int width);
        void setItemWidthDefault();

    private:
        void updateScrollbars();

    public:
        void onResize(ResizeEvent& e) override;
        void raiseOnRender(Render2DEvent& e) override;
        void raiseOnMouseButtonDown(MouseButtonDownEvent& e) override;
        void raiseOnMouseButtonUp(MouseButtonUpEvent& e) override;
        void raiseOnKeyDown(KeyDownEvent& e) override;
        void raiseOnMouseScrolled(MouseScrollEvent& e) override;
        void raiseOnMouseMoved(MouseMoveEvent& e) override;
    };
}