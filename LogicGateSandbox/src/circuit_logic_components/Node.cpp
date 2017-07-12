#include "Node.h"
#include "Circuit.h"
#include "PowerSource.h"
namespace lgs {


    void Node::updateConnected(PowerSource* power_source_that_changed,
                               bool power_source_new_value) {
        node_update_request r;
        r.power_source_new_value = power_source_new_value;
        r.power_source_that_changed = power_source_that_changed;
        for (auto it = _connections.begin(); it != _connections.end(); ++it) {
            r.node_to_update = *it;
            _circuit->requestUpdate(r);
        }
    }

    bool Node::getValue() {
        return _value;
    }


    void Node::update(const node_update_request& r) {
        bool power_source_changed = false;
        if ((_power_sources.size() == 0)) {
            for (auto it = _power_sources.begin(); it != _power_sources.end();
                 ++it) {
                if ((*it)->getValue() != true) {
                    _power_sources.erase(it);
                    power_source_changed = true;
                }
            }
        }
        if ((_power_sources.size() == 0)) {
            _value == false;
        }
        else {
            _value = true;
        }
        if (power_source_changed)
            updateConnected(r.power_source_that_changed,
                            r.power_source_new_value);
    }
}