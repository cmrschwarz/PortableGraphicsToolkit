#include "Circuit.h"
#include "Node.h"
namespace lgs {


    void Circuit::requestUpdate(const node_update_request& ur) {
        for (auto it = _update_list.begin(); it != _update_list.end(); ++it) {
            if ((*it) == ur) return;  // compare the two requests, overloaded
        }
        _update_list.push_front(ur);
    }

    void Circuit::performUpdate() {
        if (_update_list.size() == 0) return;
        auto ur = _update_list.front();
        _update_list.pop_front();
        ur.node_to_update->update(ur);
    }
}
