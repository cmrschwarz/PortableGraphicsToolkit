#pragma once
namespace pgt {
    class IFramebuffer {
        friend class IRenderingContext;

      public:
        IFramebuffer(){};
        IFramebuffer(IFramebuffer& f) = delete;
        IFramebuffer& operator=(IFramebuffer& f) = delete;
        virtual ~IFramebuffer(){};

      private:  // accessed by the friend class IRenderingContext
        virtual void bind() = 0;

      public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
    };
}