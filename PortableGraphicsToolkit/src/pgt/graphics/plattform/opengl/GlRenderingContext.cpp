#include "GlRenderingContext.h"

namespace pgt {
    namespace plattform {

        GlRenderingContext::GlRenderingContext(Window& w)
            : _default_framebuffer(w), _framebuffer(&_default_framebuffer)
        {
        }

        bool GlRenderingContext::isDefaultFramebufferEnabled() const
        {
            return (_framebuffer == &_default_framebuffer);
        }

        void GlRenderingContext::setFramebuffer(IFramebuffer& f)
        {
            _framebuffer = &f;
            bindFramebuffer(f);
        }

        void GlRenderingContext::setDefaultFramebuffer()
        {
            _framebuffer = &_default_framebuffer;
            bindFramebuffer(_default_framebuffer);
        }

        pgt::IFramebuffer& GlRenderingContext::getFramebuffer() const
        {
            return *_framebuffer;
        }
    }
}
