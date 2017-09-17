#ifndef __HAZ_FALLBACK
#define __HAZ_FALLBACK

#include <haz/Tools/Macro.hpp>
#include <haz/Allocation/Block.hpp>

BEG_NAMESPACE_HAZ_ALLOC

template<class Tmain_allocator, class Temergency_allocator>
class Fallback {
public:
    Block allocate(size_t size) {
        Block b = main_allocator.allocate(size);
        if (b.ptr == nullptr)
            return emergency_allocator.allocate(size);
        return b;
    }
    
    void deallocate(reference<Block> block) {
        if (main_allocator.owns(block)) 
            return main_allocator.deallocate(block);
        else
            return emergency_allocator.deallocate(block);
    }

    bool owns(reference_const<Block> block) const {
        return main_allocator.owns(block) || emergency_allocator.owns(block);
    }

    bool reallocate(reference<Block> block, size_t size) {
        if (main_allocator.owns(block)) 
            return main_allocator.reallocate(block, size);
        else
            return emergency_allocator.reallocate(block, size);
    }

    bool expand(reference<Block> block, size_t size) {
        if (main_allocator.owns(block)) 
            return main_allocator.expand(block, size);
        else
            return emergency_allocator.expand(block, size);
    }

    void deallocate_all() {
        main_allocator.deallocate_all();
        emergency_allocator.deallocate_all();
    }

private:
    Tmain_allocator main_allocator;
    Temergency_allocator emergency_allocator;
};

END_NAMESPACE_HAZ_ALLOC

#endif
