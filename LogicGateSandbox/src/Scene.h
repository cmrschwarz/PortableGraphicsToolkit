#pragma once
#include <vector>
#include "Node_legacy.h"
#include "Connection.h"
#include <pgt/window/gui/controls/Button.h>
#include <pgt/window/gui/controls/Panel.h>
#include <pgt/window/gui/controls/ListView.h>
namespace lgs {
    class Scene : public pgt::Panel {
    private:
        std::vector<Node_legacy*> _nodes;
        std::vector<Connection> _connections;
        pgt::vec2i _pos;
        float _zoom;
        pgt::ListView _tools_list;
        pgt::Panel _mode_panel;
        pgt::Button _connection_mode;
        pgt::Button _selection_mode;
        pgt::Button _insertion_mode;

    public:
        Scene();
        float getZoom();
        const pgt::vec2i& getPos();
        void raiseOnRender(pgt::Render2DEvent& e) override;
        void onResize(pgt::ResizeEvent& e) override;
        void onKeyDown(pgt::KeyDownEvent& e) override;

        void onTick() override;
        void connect(Port& p1, Port& p2);
        void addNode(Node_legacy& n);
    };
}