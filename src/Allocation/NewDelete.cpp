#include <haz/Allocation/NewDelete.hpp>
#include <haz/Allocation/Block.hpp>

Block NewDelete::allocate(size_t size) {
    void* ptr = ::operator new(size, ::std::nothrow);
    return (ptr == nullptr) ?
                Block::null()
            :   Block(ptr, size);
}

void NewDelete::deallocate(reference<Block> block) {
    if (block) {
        ::operator delete(block.ptr, static_cast<std::size_t>(block.size));
        block.reset();
    }
}

bool NewDelete::owns(reference_const<Block>) const {
    return true;
}

bool NewDelete::reallocate(reference<Block> block, size_t size) {
    if (expand(block, size)) {
        return true;
    } else {
        auto new_block = allocate(size);
        if (!new_block) {
            return false;
        } else {
            deallocate(block);
            if (block)
                return false;
            block_copy_content(block, new_block);
            block = new_block;
            return true;
        }
    }
}

bool NewDelete::expand(reference<Block> block, size_t size) {
    return size == block.size;
}

void NewDelete::deallocate_all() {

}