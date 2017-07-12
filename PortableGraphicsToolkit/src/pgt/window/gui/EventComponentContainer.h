#pragma once
#include <pgt/io/logger/logger.h>
namespace pgt {
    template <class BASE_T, class COMPONENT_T>
    class EventComponentContainer : public BASE_T {
      protected:
        std::vector<COMPONENT_T*> _components;

      public:
        using BASE_T::BASE_T;
        typedef COMPONENT_T ContainerComponent_t;
        typedef BASE_T ContainerBase_t;

        // can be overloaded
        typedef EventComponentContainer<BASE_T, COMPONENT_T> Container_t;

      public:
        ~EventComponentContainer()
        {
            for (auto it = _components.begin(); it != _components.end(); ++it) {
                (*it)->deleteMe();
            }
        }

      protected:
        void addComponent(COMPONENT_T& component)
        {
            _components.push_back(&component);
        }
        void removeComponent(COMPONENT_T& component)
        {
            for (auto it = _components.begin(); it != _components.end(); ++it) {
                if (*it == &component) {
                    _components.erase(it);
                    return;
                }
            }
            PGT_ASSERT(false,
                      "Failed to pop Component: it is not in the Container");
        }

      public:
        template <typename R, typename T, typename... P>
        void forwardEvent(R (T::*func)(P...), P&&... args)
        {
            for (auto it = _components.begin(); it != _components.end(); ++it) {
                ((**it).*func)(args...);
            }
        }
    };
}