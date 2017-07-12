#pragma once
#include <pgt/maths/maths.h>
#include <pgt/graphics/graphics_2d_fwd.h>
#include <pgt/window/gui/controls/DraggableControl.h>
namespace lgs {
    class Scene;
    class Node_legacy : public pgt::DraggableControl {
    protected:
        bool _received_update;

    public:
        Node_legacy() : _received_update(false){};
        ~Node_legacy(){};
        virtual bool update() = 0;
    };
}