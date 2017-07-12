#pragma once
namespace pgt {
    template <typename RET_TYPE, typename... ARGS>
    class Delegate;  // FWD

    namespace impl_details {
        template <typename RET_TYPE, typename... ARGS>
        class DelegateImpl {
            friend class Delegate<RET_TYPE, ARGS...>;

        private:
            typedef void* InstancePtr;
            typedef RET_TYPE (*UniversalFunction)(InstancePtr, ARGS...);
            typedef RET_TYPE (*FreeFunction)(ARGS...);

        private:
            InstancePtr _instance;
            UniversalFunction _func_ptr = nullptr;
            FreeFunction _lamda_func;

        public:
            template <FreeFunction func_ptr>
            inline static RET_TYPE freeFuncWrapper(InstancePtr instance,
                                                   ARGS... params) {
                return func_ptr(params...);
            }

            template <class C, RET_TYPE (C::*mem_func_ptr)(ARGS...)>
            inline static RET_TYPE memberFunctionWrapper(InstancePtr instance,
                                                         ARGS... params) {
                return ((*static_cast<C*>(instance)).*mem_func_ptr)(params...);
            }

            inline static RET_TYPE lambdaFunctionWrapper(InstancePtr instance,
                                                         ARGS... params) {
                return static_cast<DelegateImpl<RET_TYPE, ARGS...>*>(instance)
                    ->_lamda_func(params...);
            }

        public:
            template <FreeFunction func_ptr>
            void bind() {
                _func_ptr = &freeFuncWrapper<func_ptr>;
            }

            template <class C, RET_TYPE (C::*mem_func_ptr)(ARGS...)>
            void bind(C& instance) {
                _instance = (InstancePtr)(&instance);
                _func_ptr = &memberFunctionWrapper<C, mem_func_ptr>;
            }

            // only use this for lambdas. use bind<func>() instead for normal
            // functions
            void bind(FreeFunction _func) {
                _instance = this;
                _lamda_func = _func;
                _func_ptr = &lambdaFunctionWrapper;
            }

        public:
            RET_TYPE raiseUnguarded(ARGS... params) {
                return (_func_ptr)(_instance, params...);
            }
        };
    }
    template <typename RET_TYPE, typename... ARGS>
    class Delegate : public impl_details::DelegateImpl<RET_TYPE, ARGS...> {
    public:
        bool raise(RET_TYPE*, ARGS... params) {
            if (_func_ptr == nullptr) return false;
            *RET_TYPE = raiseUnguarded(params...);
            return true;
        }
    };
    template <typename... ARGS>
    class Delegate<void, ARGS...>
        : public impl_details::DelegateImpl<void, ARGS...> {
    public:
        bool raise(ARGS... params) {
            if (_func_ptr == nullptr) return false;
            raiseUnguarded(params...);
            return true;
        }
    };
}