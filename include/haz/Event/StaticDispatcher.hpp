#ifndef __HAZ_EVENT_DISPATCHER
#define __HAZ_EVENT_DISPATCHER

#include <haz/Tools/Macro.hpp>
#include <haz/Tools/ClassID.hpp>
#include <haz/Tools/TypeHelper.hpp>
#include<haz/Event/CallbackHolder.hpp>

#include <functional>
#include <vector>

BEG_NAMESPACE_HAZ_EVENT

BEG_NAMESPACE_NESTED_HIDDEN

template<typename...>
class StaticDispatcherHelper;

template<unsigned int P, unsigned int N, typename TEventF, typename... TEventList>
class StaticDispatcherHelper<Rank<P, N>, TEventF, TEventList...> : public StaticDispatcherHelper<Rank<P+1, N>, TEventList...> {
    using Base = StaticDispatcherHelper<Rank<P + 1, N>, TEventList...>;
public:
    using Base::subscribe;
    using Base::emit;

    template<typename... CBArgs>
    void subscribe(TypeE<TEventF> const&, CBArgs&&... args) {
        funcs.emplace_back(CallbackHolder<void(TEventF const&)>(args...));
    }

    template<class C>
    auto subscribe(Rank<P, N> const&, C* c) 
        -> decltype(std::declval<C>().receive(std::declval<TEventF>()), void()) {
        funcs.emplace_back(CallbackHolder<void(TEventF const&)>(c, &C::receive));
        Base::subscribe(Rank<P+1, N>{}, c);
    }

    void emit(TEventF& e) {
        for(auto& f : funcs) {
            f.invoke(e);
        }
    }

private:
    std::vector<CallbackHolder<void(TEventF const&)>> funcs {};
};

template<unsigned int N>
class StaticDispatcherHelper<Rank<N, N>> {
public:
    void subscribe() {}
    template<class C>
    void subscribe(Rank<N, N> const&, C*) {}
    void emit() {}
};

END_NAMESPACE_NESTED_HIDDEN

template<typename ... TEventList>
class StaticDispatcher {
    NS_HAZ_HIDDEN::StaticDispatcherHelper<Rank<0, TypeList<TEventList...>::size>, TEventList...> disp;

public:

    template<typename TEvent, typename... CBArgs>
    void subscribe(CBArgs&&... args) {
        static_assert(TypeIn<TEvent, TypeList<TEventList...>>, "You can't subscribe to this event, check if you insert it in the Event List");
        disp.subscribe(TypeE<TEvent>{}, std::forward<CBArgs>(args)...);
    }

    template<typename TEvent, typename C, void(C::*M)(TEvent const&) = &C::receive>
    void subscribe(C* instance) {
        static_assert(TypeIn<TEvent, TypeList<TEventList...>>, "You can't subscribe to this event, check if you insert it in the Event List");
        disp.subscribe(TypeE<TEvent>{}, instance, M);
    }

    template<typename C>
    void subscribe_all(C* instance) {
        disp.subscribe(Rank<0, TypeList<TEventList...>::size>{}, instance);
    }

    template<typename TEvent, typename... Args>
    void emit(Args&&... args) {
        static_assert(TypeIn<TEvent, TypeList<TEventList...>>, "You can't subscribe to this event, check if you insert it in the Event List");
        TEvent e(std::forward<Args>(args)...);
        disp.emit(e);
    }
};

END_NAMESPACE_HAZ_EVENT

#endif