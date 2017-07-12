#pragma once
#include <functional>
#include <pgt/io/logger/logger.h>
#include <pgt/maths/maths.h>
#include <pgt/window/gui/events/events.h>
#include <pgt/window/gui/Rectangle.h>
#include <pgt/managed_object.h>
namespace pgt {
    class EventComponent : public IManagedObject {
    public:
        EventComponent(){}
    public:
       virtual ~EventComponent(){};

    protected:
        std::function<void(Event& e)> _func;

    public:
        void setCallback(decltype(_func) func)
        {
            _func = func;
        }
        void clearCallback()
        {
            _func = decltype(_func)();
        }
        void callCallback(Event&& e)
        {
            if (_func) _func(e);
        }
        void callCallback(Event& e)
        {
            if (_func) _func(e);
        }
    };
}