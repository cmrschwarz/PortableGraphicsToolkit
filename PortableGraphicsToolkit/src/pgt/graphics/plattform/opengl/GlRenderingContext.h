#include <pgt/graphics/plattform/interface/IRenderingContext.h>
#include <pgt/window/window_fwd.h>
#include "GlFramebuffer.h"
#include "GlDefaultFramebuffer.h"
namespace pgt {
    namespace plattform {
        class GlRenderingContext : public IRenderingContext {
        private:
            IFramebuffer* _framebuffer;
            GlDefaultFramebuffer _default_framebuffer;

        public:
            GlRenderingContext(Window& w);
            bool isDefaultFramebufferEnabled() const override;
            void setFramebuffer(IFramebuffer& f) override;
            void setDefaultFramebuffer() override;
            IFramebuffer& getFramebuffer() const override;
        };
    }
}