#pragma once
#include <pgt/maths/maths.h>
// TODO: move this class to maths
namespace pgt {

    class Rectangle {
      public:
        vec2i pos;
        vec2i size;

      public:
        Rectangle(vec2i pos, vec2i size) : pos(pos), size(size){};

        Rectangle(int x, int y, int size_x, int size_y)
            : pos(x, y), size(size_x, size_y){};

        Rectangle(const Rectangle& r2) : pos(r2.pos), size(r2.size){};

        Rectangle() : pos(), size(){};

      public:
        bool contains(vec2i p) const
        {
            return ((p.x >= pos.x && p.x <= pos.x + size.x) &&
                    (p.y >= pos.y && p.y <= pos.y + size.y));
        }
        bool intersects(Rectangle& r) const
        {
        }
    };
}