#pragma once
#include <vector>
#include "Connection.h"
#include <pgt/graphics/graphics_2d.h>
#include <pgt/window/gui/Rectangle.h>
namespace lgs {
    class Node_legacy;
    class Port {
    public:
        pgt::Rectangle bounds;
        std::vector<Port*> connections;

        Node_legacy& node;
        bool value;
        Port(Node_legacy& node) : Port(node, 0) {}
        Port(Node_legacy& node, bool value)
            : value(value), node(node), bounds(0, 0, 15, 15) {}

        void render(pgt::Renderer2D& r);
        void pollState();
    };
}