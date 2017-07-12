#pragma once
#include <typeinfo>
namespace pgt {
    class Event {
      public:
      public:
        Event(){};
        virtual ~Event(){};

      public:
        template <class C>
        bool is()
        {
            return typeid(C) == typeid(*this);
        }
        template <class C>
        C& cast()
        {
            return static_cast<C&>(*this);
        }
    };
}