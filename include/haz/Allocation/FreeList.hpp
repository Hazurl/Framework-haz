#ifndef __HAZ_FREE_LIST
#define __HAZ_FREE_LIST

#include <haz/Allocation/Block.hpp>
#include <haz/Tools/Macro.hpp>
#include <haz/Tools/TypeInfo.hpp>

BEG_NAMESPACE_HAZ_ALLOC

template<typename Alloc, size_t size_min, size_t size_max>
class FreeList {
    Alloc allocator;
    struct Node {
        Node* next = nullptr;
        Block block;
    };

    Node* root = nullptr;

public:

    ~FreeList() {
        deallocate_all();
    }

    Block allocate(size_t size) {
        if (size > size_min && size <= size_max) {
            if (root) {
                Node* current = root;
                root = root->next;
                Block b = current->block;
                delete current;
                b.size = size;
                return b;
            } else {
                auto b = allocator.allocate(size_max);
                b.size = size;
                return b;
            }
        } else {
            return allocator.allocate(size);
        }
    }

    void deallocate(reference<Block> b) {
        if (b.size > size_min && b.size <= size_max) {
            root = new Node({root, b});
            b = Block::null();
            return;
        } else {
            allocator.deallocate(b);
        }
    }

    bool expand(reference<Block> b, size_t size) {
        if (b.size > size_min && b.size <= size_max) {
            if (size > size_min && size <= size_max) {
                b.size = size;
                return true;
            }
            return false;
        } else {
            return allocator.extend(b, size);
        }
    }

    bool reallocate(reference<Block> block, size_t size) {
        if (expand(block, size)) {
            return true;
        } else {
            auto new_block = allocate(size);
            if (!new_block) {
                return false;
            } else {
                deallocate(block);
                if (block) {
                    deallocate(new_block);
                    return false;
                }

                block_copy_content(block, new_block);
                block = new_block;
                return true;
            }
        }
    }

    bool owns(Block const& block) {
        return allocator.owns(block);
    }

    void deallocate_all() {
        while(root != nullptr) {
            allocator.deallocate(root->block);
            auto node = root->next;
            delete root;
            root = node;
        }
    }

};

END_NAMESPACE_HAZ_ALLOC

#endif