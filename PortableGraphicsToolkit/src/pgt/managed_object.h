#pragma once
namespace pgt {
    class IManagedObject {
    public:
        virtual ~IManagedObject(){}
    public:
        virtual void deleteMe(){};
    };
    namespace internal {
        // this ugly name was chosen to help people not stumbling over it in
        // IDEs
        template <class COMPONENT_T>
        class Internal_ManagedObject : public COMPONENT_T {
        public:
            using COMPONENT_T::COMPONENT_T;
            void deleteMe() override
            {
                delete this;
            }
        };
    }
    template <class C, typename... ARGS>
    inline C& new_mo(ARGS&&... params)
    {
        return *new internal::Internal_ManagedObject<C>(
            std::forward<ARGS>(params)...);
    }
}
