#ifndef __HAZ_BRANCH
#define __HAZ_BRANCH

#include <haz/Tools/Macro.hpp>
#include <haz/Allocation/Block.hpp>

BEG_NAMESPACE_HAZ_ALLOC

template<size_t limit, typename Tunder_allocator, typename Tabove_allocator>
class Branch {
public:
    ~Branch() {}

    Block allocate(size_t size) {
        if (size > limit) {
            return above_allocator.allocate(size);
        } else {
            return under_allocator.allocate(size);
        }
    }
    
    void deallocate(reference<Block> block) {
        if (block.size > limit) {
            return above_allocator.deallocate(block);
        } else {
            return under_allocator.deallocate(block);
        }
    }

    bool owns(reference_const<Block> block) const {
        if (block.size > limit) {
            return above_allocator.owns(block);
        } else {
            return under_allocator.owns(block);
        }
    }

    bool reallocate(reference<Block> block, size_t size) {
        if (block.size > limit) {
            if (size > limit) {
                return above_allocator.reallocate(block, size);
            }
        } else {
            if (size <= limit) {
                return under_allocator.reallocate(block, size);
            }
        }
        return false;
    }

    bool expand(reference<Block> block, size_t size) {
        if (block.size > limit) {
            if (size > limit) {
                return above_allocator.expand(block, size);
            }
        } else {
            if (size <= limit) {
                return under_allocator.expand(block, size);
            }
        }
        return false;    
    }

    void deallocate_all() {
        above_allocator.deallocate_all();
        under_allocator.deallocate_all();
    }

private:
    Tunder_allocator under_allocator;
    Tabove_allocator above_allocator;
};

END_NAMESPACE_HAZ_ALLOC

#endif
