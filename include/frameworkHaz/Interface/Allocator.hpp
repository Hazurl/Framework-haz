#ifndef __HAZ_ALLOCATOR
#define __HAZ_ALLOCATOR

#include <frameworkHaz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

template<typename TType, typename ...TArgs>
class Allocator {
public:
    virtual ~Allocator() = 0;

    virtual TType* allocate(TArgs ... args) = 0;
    virtual void deallocate(TType* t) = 0;
};

template<typename TType, typename ...TArgs>
Allocator<TType, TArgs...>::~Allocator() {}

template<typename TType, typename ...TArgs>
class DefaultAllocator : public Allocator<TType, TArgs...> {
public:

    virtual TType* allocate(TArgs ... args) {
        return new TType(args...);
    }

    virtual void deallocate(TType* t) {
        delete t;
        t = nullptr;
    }

};

END_NAMESPACE_HAZ

#endif
