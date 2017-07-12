#pragma once
#include <pgt/maths/maths.h>
#include <pgt/graphics/Color.h>
#include <pgt/io/istreams/IStreamReader.h>
#include <pgt/graphics/plattform/interface/ITexture.h>
#include <pgt/graphics/plattform/interface/IFONT.h>
#include <pgt/window/window_fwd.h>
#include <pgt/graphics/graphics_2d_fwd.h>
namespace pgt {
    class IRenderer2D {
    public:
        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void pushViewport(const vec2i& pos, const vec2i& size) = 0;
        virtual void popViewport() = 0;

    public:
        virtual void setColor(Color c) = 0;
        virtual void drawLine(const vec2i& start, const vec2i& end,
                              int thickness) = 0;
        virtual void drawRectangle(const vec2i& start, const vec2i& size,
                                   size_t thickness) = 0;
        virtual void fillTriangle(const vec2i& pos0, const vec2i& pos1,
                                  const vec2i& pos2) = 0;
        virtual void fillQuad(const vec2i& pos0, const vec2i& pos1,
                              const vec2i& pos2, const vec2i& pos3) = 0;
        virtual void fillCircle(const vec2i& center, size_t radius,
                                float angle = 2 * M_PI,
                                float start_angle = 0) = 0;
        virtual void drawTexture(const ITexture& t, const vec2i& pos,
                                 const vec2i& size) = 0;
        virtual void fillRectangle(const vec2i& start, const vec2i& size) = 0;
        virtual void drawString(const std::string& text, vec2i position) = 0;
        virtual vec4i getCurrentViewport() const = 0;

    public:
        virtual void setFont(const Font& f) = 0;
        virtual const Font& getFont() const = 0;
    };
}
