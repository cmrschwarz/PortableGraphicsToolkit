#pragma once
#include <deque>
#include "node_update_request.h"
namespace lgs {

    class Circuit {
    private:
        // TODO: make better containers
        std::deque<node_update_request> _update_list;

    public:
        void requestUpdate(const node_update_request& ur);
        void performUpdate();

    private:
    };
}