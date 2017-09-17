#ifndef __HAZ_AFIX_ALLOC
#define __HAZ_AFIX_ALLOC

#include <type_traits>

#include <haz/Allocation/Block.hpp>
#include <haz/Tools/Macro.hpp>
#include <haz/Tools/TypeInfo.hpp>

BEG_NAMESPACE_HAZ_ALLOC

struct no_afix {};

template<typename Alloc, typename Prefix = no_afix, typename Sufix = no_afix>
class Afix {
    Alloc allocator;

    using TThis = Afix<Alloc, Prefix, Sufix>;
    
public:
    static constexpr bool has_prefix = !std::is_same<no_afix, Prefix>::value;
    static constexpr bool has_sufix = !std::is_same<no_afix, Sufix>::value;
    
    static constexpr size_t size_prefix = has_prefix ? sizeof(Prefix) : 0;
    static constexpr int offset_prefix = has_prefix ? -size_prefix : 0;
    static constexpr size_t size_sufix = has_sufix ? sizeof(Sufix) : 0;    
    static constexpr size_t size_added = size_prefix + size_sufix;

public:

    Block allocate(size_t size) {
        size_t real_size = size + size_added;
        auto real_block = allocator.allocate(real_size);
        if (!real_block)
            return real_block;

        auto block = to_inner_block(real_block);
        if (has_prefix)
            new (prefix(block)) Prefix;
        if (has_sufix)
            new (sufix(block)) Sufix;
        return block;
    }

    void deallocate(reference<Block> block) {
        if (block) {
            auto real_block = to_real_block(block);
            if (has_prefix)
                prefix(block)->~Prefix();
            if (has_sufix)
                sufix(block)->~Sufix();
            allocator.deallocate(real_block);
            if (!real_block) {
                block = Block::null();
            }
        }
    }

    bool owns(reference_const<Block> block) {
        return allocator.owns(to_real_block(block));
    }

    bool expand(reference<Block> block, size_t size) {
        size_t new_real_size = size_added + size;
        Block real_block = to_real_block(block);
        if (allocator.expand(real_block, new_real_size)) {
            auto new_block = to_inner_block(real_block);
            if (has_sufix)
                move_sufix(block, new_block);
            block = new_block;
            return true;
        }

        return false;
    }

    bool reallocate(reference<Block> block, size_t size) {
        if (expand(block, size)) {
            return true;
        } else {
            auto new_block = allocate(size);
            if (!new_block)
                return false;
            copy_block_with_afix(block, new_block);
            deallocate(block);
            if (block) {
                deallocate(new_block);
                return false;
            }
            block = new_block;
            return true;
        }
    }

    void deallocate_all() {
        allocator.deallocate_all();
    }

    static Prefix* prefix(reference<Block> block) {
        if (!block || !has_prefix)
            return nullptr;
        return static_cast<Prefix*>(
            block.ptr_offset(offset_prefix)
        );
    }

    inline Prefix* prefix_of(reference<Block> block) {
        return TThis::prefix(block);
    }

    static Sufix* sufix(reference<Block> block) {
        if (!block || ! has_sufix)
            return nullptr;
        return static_cast<Sufix*>(
            block.ptr_offset(block.size)
        );
    }

    inline Sufix* sufix_of(reference<Block> block) {
        return TThis::sufix(block);
    }

    static Block inner_block(reference<Prefix> prefix, size_t size) {
        return Block(reinterpret_cast<void*>(reinterpret_cast<char*>(&prefix) - offset_prefix), size);
    }

    inline Block inner_block_of(reference<Prefix> prefix, size_t size) {
        return TThis::inner_block(prefix, size);
    }

    static Block inner_block(reference<Sufix> sufix, size_t size) {
        return Block(reinterpret_cast<void*>(reinterpret_cast<char*>(&sufix) - size), size);
    }

    inline Block inner_block_of(reference<Sufix> sufix, size_t size) {
        return TThis::inner_block(sufix, size);
    }

private:

    Block to_real_block(reference<Block> block) {
        return { block.ptr_offset(offset_prefix), block.size + size_added };
    }

    Block to_inner_block(reference<Block> real_block) {
        return { real_block.ptr_offset(size_prefix), real_block.size - size_added };
    }

    void move_sufix(reference<Block> from, reference<Block> to) {
        if (!has_sufix)
            return;
        std::memmove(
            to.ptr_offset(to.size),
            from.ptr_offset(from.size),
            size_sufix
        );
    }

    void copy_block_with_afix(reference<Block> from, reference<Block> to) {
        block_copy_content(to_real_block(from), to_real_block(to));
    }

};

END_NAMESPACE_HAZ_ALLOC

#endif