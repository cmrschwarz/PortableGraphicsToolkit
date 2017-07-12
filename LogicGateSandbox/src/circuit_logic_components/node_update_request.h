#pragma once

namespace lgs {
    class Node;
    class PowerSource;
    struct node_update_request {
        bool power_source_new_value;
        Node* node_to_update;
        PowerSource* power_source_that_changed;
        bool operator==(const node_update_request& rhs) {
            return (node_to_update == rhs.node_to_update &&
                    power_source_that_changed ==
                        rhs.power_source_that_changed &&
                    power_source_new_value == rhs.power_source_new_value);
        }
    };
}