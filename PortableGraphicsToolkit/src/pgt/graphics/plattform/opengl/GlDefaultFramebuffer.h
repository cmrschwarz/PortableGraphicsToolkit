#pragma once
#include <pgt/graphics/plattform/interface/IFramebuffer.h>
#include <pgt/window/window_fwd.h>
namespace pgt {
    namespace plattform {
        class GlDefaultFramebuffer : public IFramebuffer {
          private:
            const Window& _window;

          public:
            GlDefaultFramebuffer(const Window& window);

          public:
            int getWidth() const override;
            int getHeight() const override;
            void bind() override;
        };
    }
}