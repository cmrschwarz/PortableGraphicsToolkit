#pragma once
#include <algorithm>
#include <vector>
namespace pgt {
    template <class CONTAINER_T>
    void removeFast(CONTAINER_T& container, typename CONTAINER_T::iterator el)
    {
        std::swap(el, container.end());
        container.pop_back();
    }
    template <class CONTAINER_T>
    void removeVal(CONTAINER_T& container, const typename CONTAINER_T::value_type& v)
    {
        for (auto it = container.begin(); it != container.end(); ++it) {
            std::erase(it);
        }
    }
    template <class CONTAINER_T>
    void removeValFast(CONTAINER_T& container, const typename CONTAINER_T::value_type& v)
    {
        for (auto it = container.begin(); it != container.end(); ++it) {
            removeFast(container, it);
        }
    }
}