#ifndef __HAZ_CALLBACKHOLDER
#define __HAZ_CALLBACKHOLDER

#include <haz/Tools/Macro.hpp>
#include <functional>

BEG_NAMESPACE_HAZ_EVENT

template<typename TRes, typename ... Args>
class CallbackHolder;

template<typename TRes, typename ... Args>
class CallbackHolder<TRes(Args...)> {
public:

    using std_function = std::function<TRes(Args...)>;
    using function = TRes(*)(Args...);
    template<class C>
    using method = TRes(C::*)(Args...);
    using self = CallbackHolder<TRes(Args...)>;

private:

    class Holder {
    public:
        virtual ~Holder() {}
        virtual TRes invoke(Args&&... args) = 0;
    };

    class FunctionHolder : public Holder {
    public:
        using TFunc = std_function;

        FunctionHolder(TFunc f) : f(f) {}
        virtual ~FunctionHolder() {};

        virtual TRes invoke(Args&&... args) override {
            return f(std::forward<Args>(args)...);
        }

    private:
        TFunc f;
    };

    template<class C>
    class MethodHolder : public Holder {
    public:
        using TFunc = method<C>; 

        MethodHolder(C* c, TFunc m) : c(c), m(m) {}
        virtual ~MethodHolder() {}

        virtual TRes invoke(Args&&... args) override {
            return (c->*m)(std::forward<Args>(args)...);
        }

    private:
        C* c;
        TFunc m;
    };

    Holder* holder = nullptr;

public:
    
    CallbackHolder(std_function f) : holder(new FunctionHolder(f)) {}
    template<typename C> CallbackHolder(C* instance, method<C> m) : holder(new MethodHolder<C>(instance, m)) {}
    
    CallbackHolder(self&& o) : holder(o.holder) { o.holder = nullptr; }
    CallbackHolder(self const& o) = delete;
    
    ~CallbackHolder() { if (holder) delete holder; }

    TRes invoke(Args&&... args) {
        return holder->invoke(std::forward<Args>(args)...);
    }
};

END_NAMESPACE_HAZ_EVENT

#endif
