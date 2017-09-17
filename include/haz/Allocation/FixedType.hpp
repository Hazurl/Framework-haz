#ifndef __HAZ_FIXEDTYPE_ALLOCATOR
#define __HAZ_FIXEDTYPE_ALLOCATOR

#include <haz/Tools/Macro.hpp>
#include <haz/Allocation/Block.hpp>
#include <haz/Allocation/NewDelete.hpp>
#include <haz/Tools/TypeInfo.hpp>

BEG_NAMESPACE_HAZ_ALLOC

template<typename T, class Allocator = NewDelete>
class FixedType {
    Allocator allocator;

    FixedType(Allocator& allocator) : allocator(allocator) {}

public:
    FixedType() {}

    using TBlock = Block_type<T>;

    template<typename U>
    FixedType<U, Allocator> bind() {
        return { allocator };
    }

    Allocator& getAllocator () {
        return allocator;
    }

    TBlock allocate (size_t num) {
        Block b = allocator.allocate(num * sizeof(T));
        if (!b) return TBlock::null();
        return b. Block::template cast_to<T>();
    }


    void deallocate (reference<TBlock> block) {
        auto b = block. TBlock::template cast_to<void>();
        allocator.deallocate(b);
        block = b. Block::template cast_to<T>();
    }

    template<typename ...Args>
    void construct(T* t, Args && ...args) {
        if (t) {
            new (t) T(args...);
        }
    }

    void destroy(T* t) {
        if (t) {
            t->~T();
        }
    }
};

END_NAMESPACE_HAZ_ALLOC

#endif