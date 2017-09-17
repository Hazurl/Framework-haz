#ifndef __HAZ_STACK
#define __HAZ_STACK

#include <haz/Tools/Macro.hpp>
#include <haz/Allocation/Block.hpp>

BEG_NAMESPACE_HAZ_ALLOC

template<size_t total_size>
class Stack {
public:
    Stack() : p(stack) { std::cout << "Oncreation " << (void*)p << " =? " << (void*)stack << std::endl; }
    ~Stack() {}

    Block allocate(size_t size) {
        size_t size_align = align_up(size);
        if (last - p < size) {
            return Block::null();
        }

        Block block(p, size);
        p += size_align;
        return block;
    }

    void deallocate(reference<Block> block) {
        char* block_ptr_char = block.ptr_char();
        if (block_ptr_char + align_up(block.size) == p) {
            p = block_ptr_char;
            block.reset();
        }
    }

    bool owns(reference_const<Block> block) const {
        return (block.ptr >= stack) 
            && (block.ptr < last);
    }

    bool reallocate(reference<Block> block, size_t size) {
        return expand(block, size);
    }

    bool expand(reference<Block> block, size_t new_size) {
        if (!owns(block))
            return false;

        if (align_up(block.size) >= new_size) {
            block.size = new_size;
            return true;
        }
        
        size_t new_size_align = align_up(new_size);
        size_t size_align     = align_up(block.size);
        if (block.ptr_offset(size_align) == p // dernier ?
            && (new_size < block.size          // reduction ?
            || last - p > new_size))           // place ?
        {
            p = p - size_align + new_size_align;
            block.size = new_size;
            return true;
        }
        return false;
    }

    void deallocate_all() {
        p = stack;
    }

private:

    char stack [total_size];
    char* p;
    char* const last = stack + total_size;

};

END_NAMESPACE_HAZ_ALLOC

#endif
