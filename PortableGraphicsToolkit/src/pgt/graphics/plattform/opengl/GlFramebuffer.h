#pragma once
#include <pgt/graphics/plattform/interface/ITexture.h>
#include <pgt/graphics/plattform/interface/IFramebuffer.h>
#include <pgt/utils/primitives.h>
namespace pgt {
    namespace plattform {
        class GlFramebuffer : public IFramebuffer {
          private:
            GLuint _fbo_id;
            size_t _width;
            size_t _height;

          public:
            GlFramebuffer(size_t width, size_t height, bool color_buffer,
                          bool depth_buffer, ITexture* t_color,
                          ITexture* t_depth);
            ~GlFramebuffer();
            GlFramebuffer(GlFramebuffer&& rhs);
            GlFramebuffer& operator=(GlFramebuffer&& rhs);

          public:
            int getWidth() const override;
            int getHeight() const override;

          private:
            void bind() override;

          private:
            void attachColorBuffer();
            void attatchColorTexture(ITexture& t);
            void attatchDepthBuffer();
            void attatchDepthTexture(ITexture& t);
            GLuint getFBOID();

          private:
            GlFramebuffer(GlFramebuffer& rhs) = delete;
            GlFramebuffer& operator=(GlFramebuffer& rhs) = delete;
        };
    }
}