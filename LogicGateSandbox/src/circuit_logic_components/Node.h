#pragma once
#include <vector>
#include "node_update_request.h"
namespace lgs {
    class Circuit;
    class PowerSource;
    class Node {
    protected:
        Circuit* _circuit;
        std::vector<Node*> _connections;
        std::vector<PowerSource*> _power_sources;
        bool _value;

    public:
        Node();
        ~Node();

    public:
        virtual void update(const node_update_request& r);
        bool getValue();
        void updateConnected(PowerSource* power_source_that_changed,
                             bool power_source_new_value);
    };
}
