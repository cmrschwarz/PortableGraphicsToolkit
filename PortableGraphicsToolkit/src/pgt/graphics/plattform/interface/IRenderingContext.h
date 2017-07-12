#pragma once
#include <pgt/graphics/plattform/opengl/font/GlFontManager.h>
#include <pgt/window/window_fwd.h>
#include <pgt/graphics/plattform/interface/IFramebuffer.h>
#include "IFontManager.h"
namespace pgt {
    class IRenderingContext {
    public:
        virtual ~IRenderingContext(){};

    public:
        // This is deprecated. don't use it
        virtual void setContextCurrent() = 0;

        // TODO: refactor
        virtual IFontManager& getFontManager() = 0;

        virtual Window& getWindow() const = 0;
        virtual bool isDefaultFramebufferEnabled() const = 0;
        virtual IFramebuffer& getFramebuffer() const = 0;
        virtual void setFramebuffer(IFramebuffer& f) = 0;
        virtual void setDefaultFramebuffer() = 0;

    protected:
        static void bindFramebuffer(IFramebuffer& f)
        {
            f.bind();
        }
    };
}