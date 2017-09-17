#ifndef __HAZ_SINGLEEVENTDISPATCHER
#define __HAZ_SINGLEEVENTDISPATCHER

#include <haz/Tools/Macro.hpp>
#include <haz/Event/CallbackHolder.hpp>

#include <functional>
#include <vector>

BEG_NAMESPACE_HAZ_EVENT

template<typename T>
class SingleEventDispatcher {
public:
    using TFunc = CallbackHolder<void(T const&)>;
    
    void emit(T const& event) {
        for(auto& f : funcs) {
            f.invoke(event);
        }
    }

    void subscribe(TFunc f) {
        funcs.emplace_back(std::move(f));
    }
    
private:
    std::vector<TFunc> funcs {};
};

END_NAMESPACE_HAZ_EVENT

#endif
