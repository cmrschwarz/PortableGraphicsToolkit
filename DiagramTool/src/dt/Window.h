#pragma once
#include <pgt/window/gui/GuiWindow.h>
#include "Table.h"
#include "Diagram.h"

namespace dt {

    class Window : public pgt::GuiWindow {
      private:
        Diagram _diagram;

      public:
        ~Window();
        Window(dt::Table& t);
        void setClickCallback(CallbackFun fun);

      private:
        void init();
        static pgt::window_creation_hints getHints();
        std::string getAvailableImageName();
    };
}  // namespace dt