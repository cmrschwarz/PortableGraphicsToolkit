#include "GlFramebuffer.h"
#include <GL/glew.h>
#include <pgt/graphics/plattform/opengl/GlTexture.h>

#include <pgt/io/logger/logger.h>
#include <pgt/window/window.h>
namespace pgt {
    namespace plattform {
        GlFramebuffer::GlFramebuffer(size_t width, size_t height,
                                     bool color_buffer, bool depth_buffer,
                                     ITexture* t_color, ITexture* t_depth)
            : _width(width), _height(height)
        {
            glGenFramebuffers(1, &_fbo_id);
            glBindFramebuffer(GL_FRAMEBUFFER, _fbo_id);
            if (color_buffer) {
                if (t_color)
                    attatchColorTexture(*t_color);
                else
                    attachColorBuffer();
                glDrawBuffer(GL_COLOR_ATTACHMENT0);
            }
            else {
                glDrawBuffer(0);
                glReadBuffer(0);
            }
            if (depth_buffer) {
                if (t_depth) {
                    attatchDepthTexture(*t_depth);
                }
                else {
                    attatchDepthBuffer();
                }
            }
            engine::internal::checkGLErrors(
                "GL Error during Framebuffer Creation");
            GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            PGT_ASSERT(status == GL_FRAMEBUFFER_COMPLETE,
                      "OpenGL Framebuffer creation error %i", status);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        GlFramebuffer::GlFramebuffer(GlFramebuffer&& f)
        {
            *this = std::move(f);
        }

        int GlFramebuffer::getWidth() const
        {
            return _width;
        }

        int GlFramebuffer::getHeight() const
        {
            return _height;
        }

        GlFramebuffer& GlFramebuffer::operator=(GlFramebuffer&& f)
        {
            std::swap(_fbo_id, f._fbo_id);
            _width = f._width;
            _height = f._height;

            return *this;
        }
        GlFramebuffer::~GlFramebuffer()
        {
            glDeleteFramebuffers(1, &_fbo_id);
        }

        void GlFramebuffer::bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, _fbo_id);
            glViewport(0, 0, _width, _height);
            int gl_err = glGetError();
        }

        void GlFramebuffer::attachColorBuffer()
        {
            GLuint color_buffer;
            glGenRenderbuffers(1, &color_buffer);
            glBindRenderbuffer(GL_RENDERBUFFER, color_buffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, _width, _height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                      GL_RENDERBUFFER, color_buffer);
        }

        void GlFramebuffer::attatchColorTexture(ITexture& t)
        {
            auto& tc = static_cast<GlTexture&>(t);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                   GL_TEXTURE_2D, tc.getTID(), 0);
        }

        void GlFramebuffer::attatchDepthBuffer()
        {
            GLuint depth_buffer;
            glGenRenderbuffers(1, &depth_buffer);
            glBindRenderbuffer(GL_RENDERBUFFER, depth_buffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width,
                                  _height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                      GL_RENDERBUFFER, depth_buffer);
        }

        void GlFramebuffer::attatchDepthTexture(ITexture& t)
        {
            auto& tc = static_cast<GlTexture&>(t);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                   GL_TEXTURE_2D, tc.getTID(), 0);
        }

        GLuint GlFramebuffer::getFBOID()
        {
            return _fbo_id;
        }
    }
}