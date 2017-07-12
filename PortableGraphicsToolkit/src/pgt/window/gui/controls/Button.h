#pragma once
#include "RectangularControl.h"
#include <pgt/graphics/plattform/opengl/2d/GlRenderer2D.h>
namespace pgt {
    class Button : public RectangularControl {
    private:
        Color _back_color = Color::DARK_GRAY;
        Color _text_color = Color::WHITE;
        std::string _text;
        pgt::Font _font;
        vec2i _str_pos;


    public:
        Button();

    public:
        void onRender(Render2DEvent& re) override;
        void raiseOnResize(ResizeEvent& e) override;
        void raiseOnPositionChanged(PositionChangedEvent& e) override;

    public:
        void setFont(const Font& f);
        void setText(const std::string& s);
        Color getBackColor() const;
        Color getTextColor() const;
        void setBackColor(Color c);
        void setTextColor(Color c);

    private:
        void updateStringPos();
    };
}