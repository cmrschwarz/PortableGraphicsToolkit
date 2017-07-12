#include "Button.h"
#include <pgt/window/window.h>
namespace pgt {

    Button::Button()
        : _font(engine::getRenderingContextCurrent()
                    .getFontManager()
                    .getDefaultFont())
    {
    }

    void Button::onRender(Render2DEvent& re)
    {
        re.renderer.setColor(_back_color);
        re.renderer.fillRectangle(_bounds.pos, _bounds.size);
        re.renderer.setColor(_text_color);
        re.renderer.setFont(_font);
        re.renderer.drawString(_text, _str_pos);
    }


    void Button::raiseOnResize(ResizeEvent& e)
    {
        updateStringPos();
        RectangularControl::raiseOnResize(e);
    }

    void Button::raiseOnPositionChanged(PositionChangedEvent& e)
    {
        updateStringPos();
        RectangularControl::raiseOnPositionChanged(e);
    }

    void Button::setFont(const Font& f)
    {
        _font = f;
        updateStringPos();
    }

    void Button::setText(const std::string& s)
    {
        _text = s;
        updateStringPos();
    }

    pgt::Color Button::getBackColor() const
    {
        return _back_color;
    }

    pgt::Color Button::getTextColor() const
    {
        return _text_color;
    }

    void Button::setBackColor(Color c)
    {
        _back_color = c;
    }

    void Button::setTextColor(Color c)
    {
        _text_color = c;
    }

    void Button::updateStringPos()
    {
        _str_pos = vec2i(
            pgt::max((getBounds().size.x - _font.measureString(_text).x) / 2, 0),
            (getBounds().size.y - _font.getYOffsetMax()) / 2);
        _str_pos += getBounds().pos;
    }
}