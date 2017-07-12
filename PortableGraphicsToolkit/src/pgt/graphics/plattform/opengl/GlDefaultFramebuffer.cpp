#include "GlDefaultFramebuffer.h"
#include <pgt/window/window.h>
#include <GL/glew.h>
namespace pgt {
    namespace plattform {

        GlDefaultFramebuffer::GlDefaultFramebuffer(const Window& window)
            : _window(window)
        {
        }

        int GlDefaultFramebuffer::getWidth() const
        {
            return _window.getWidth();
        }

        int GlDefaultFramebuffer::getHeight() const
        {
            return _window.getHeight();
        }

        void GlDefaultFramebuffer::bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, getWidth(), getHeight());
        }
    }
}
