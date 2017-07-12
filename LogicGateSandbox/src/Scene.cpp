#include "Scene.h"
#include <pgt/graphics/graphics_2d.h>
#include "Button.h"
#include "LED.h"
#include "Connection.h"
#include "NAND.h"
#include "NOT.h"
#include <pgt/window/gui/controls/ListView.h>
#include <pgt/window/gui/controls/VerticalScrollbar.h>
#include <pgt/window/gui/controls/HorizontalScrollbar.h>
#include <pgt/window/window.h>
#include <pgt/utils/debug/MessageBoxes.h>
#include "GateListViewItem.h"
#include <pgt/window/engine.h>
namespace lgs {
    Scene::Scene() {
        // PERMANENT
        _tools_list.setVerticalScrollbarVisibility(
            pgt::ListView::ALWAYS_VISIBLE);

        addControl(_tools_list);

        addControl(_mode_panel);

        _connection_mode.setText("Connection Mode");
        _connection_mode.setBounds(pgt::Rectangle(140, 0, 140, 25));
        _connection_mode.setCallback([&](pgt::Event& e) {
            if (e.is<pgt::FocusGainedEvent>()) {
                _connection_mode.setBackColor(pgt::Color::WINDOW_BLUE);
            }
            if (e.is<pgt::FocusLostEvent>()) {
                _connection_mode.setBackColor(pgt::Color::DARK_GRAY);
            }
        });
        _mode_panel.addControl(_connection_mode);


        _selection_mode.setText("Selection Mode");
        _selection_mode.setBounds(pgt::Rectangle(0, 0, 140, 25));
        _selection_mode.setCallback([&](pgt::Event& e) {
            if (e.is<pgt::FocusGainedEvent>()) {
                _selection_mode.setBackColor(pgt::Color::WINDOW_BLUE);
            }
            if (e.is<pgt::FocusLostEvent>()) {
                _selection_mode.setBackColor(pgt::Color::DARK_GRAY);
            }
        });
        _mode_panel.addControl(_selection_mode);

        _insertion_mode.setText("Insertion Mode");
        _insertion_mode.setBounds(pgt::Rectangle(280, 0, 140, 25));
        _insertion_mode.setCallback([&](pgt::Event& e) {
            if (e.is<pgt::FocusGainedEvent>()) {
                _insertion_mode.setBackColor(pgt::Color::WINDOW_BLUE);
            }
            if (e.is<pgt::FocusLostEvent>()) {
                _insertion_mode.setBackColor(pgt::Color::DARK_GRAY);
            }
        });
        _mode_panel.addControl(_insertion_mode);

        // TEMP
        for (int i = 0; i < 20; i++) {
            _tools_list.addItem(pgt::new_mo<GateListViewItem>());
        }
        auto& b = pgt::new_mo<lgs::Button>();
        auto& b2 = pgt::new_mo<lgs::Button>();
        auto& l = pgt::new_mo<LED>();
        auto& n = pgt::new_mo<NAND>();
        auto& l2 = pgt::new_mo<LED>();
        auto& n2 = pgt::new_mo<NOT>();
        auto& b3 = pgt::new_mo<lgs::Button>();

        addNode(b);
        addNode(b2);
        addNode(l);
        addNode(n);
        connect(b.getPort(), n.getInput1());
        connect(b2.getPort(), n.getInput2());
        connect(n.getOutput(), l.getPort());
        addNode(l2);
        addNode(n2);
        addNode(b3);
        connect(l2.getPort(), n2.getOutput());
        connect(b3.getPort(), n2.getInput1());
        connect(n2.getOutput(), n2.getInput1());
        l2.setBounds(pgt::Rectangle(100, 100, 50, 50));
    };

    float Scene::getZoom() {
        return _zoom;
    }

    const pgt::vec2i& Scene::getPos() {
        return _pos;
    }

    void Scene::raiseOnRender(pgt::Render2DEvent& e) {
        e.renderer.setColor(pgt::Color::LIGHT_GRAY);
        e.renderer.fillRectangle(getBounds().pos, getBounds().size);
        Panel::raiseOnRender(e);
        for (auto it = _connections.begin(); it != _connections.end(); ++it) {
            (*it).render(e.renderer);
        }
    }

    void Scene::onResize(pgt::ResizeEvent& e) {
        _tools_list.setBounds(pgt::Rectangle(0, 0, 250, getBounds().size.y));
        _mode_panel.setBounds(
            pgt::Rectangle(250, 0, getBounds().size.x - 250, 25));
    }


    void Scene::onKeyDown(pgt::KeyDownEvent& e) {
        if (e.key == pgt::KEY_ESCAPE) pgt::engine::terminateApp();
    }

    void Scene::onTick() {
        bool change;
        int it = 0;
        do {
            change = false;
            for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
                change = change || (*it)->update();
            }
            it++;
        } while (change == true && it < 50);
        if (change && pgt::engine::getApp().isEventBased()) {
            pgt::engine::getApp().requestEventBased(false);
        }
    }

    void Scene::connect(Port& p1, Port& p2) {
        Connection c(p1, p2);
        _connections.push_back(c);
        p1.connections.push_back(&p2);
        p2.connections.push_back(&p1);
    }

    void Scene::addNode(Node_legacy& n) {
        addControl(n);
        _nodes.push_back(&n);
    }
}
