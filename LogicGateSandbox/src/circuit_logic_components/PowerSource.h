#pragma once
#include "Node.h"
#include <pgt/utils/algorithms.h>
namespace lgs {
    class PowerSource : public Node {
    public:
        bool _emmitting_signal;

    public:
        void setEmmitingValue(bool emm_val) {
            if (_emmitting_signal != emm_val) {
                _emmitting_signal = emm_val;
                if (emm_val) {
                    _power_sources.push_back(this);
                }
                else {
                    pgt::removeValFast(_power_sources, this);
                }
            }
        }
        void update(const node_update_request& r) {}
    };
}