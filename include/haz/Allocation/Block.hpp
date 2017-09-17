#ifndef __HAZ_BASEALLOCATOR
#define __HAZ_BASEALLOCATOR

#include <haz/Tools/Macro.hpp>
#include <haz/Tools/TypeInfo.hpp>
#include <haz/Tools/Utility.hpp>

#include <cstring>

BEG_NAMESPACE_HAZ_ALLOC

using size_t = unsigned int;

template<typename T>
struct Block_type {
    Block_type() : ptr(nullptr), size(0) {}
    Block_type(pointer<T> ptr, size_t size) : ptr(ptr), size(size) {}
    Block_type(reference_const<Block_type<T>> b) : Block_type(b.ptr, b.size) {}
    Block_type(rvalue<Block_type<T>> b) { *this = std::move(b); }
    reference<Block_type<T>> operator = (reference_const<Block_type<T>> b) = default;
    reference<Block_type<T>> operator = (rvalue<Block_type<T>> b) {
        ptr = b.ptr;
        size = b.size;
        b.reset();
        return *this;
    }

    template<typename U>
    Block_type<U> cast_to() {
        return { static_cast<pointer<U>>(ptr), size };
    }

    pointer<T> ptr = nullptr;
    size_t size = 0;

    static Block_type<T>&& null() {
        return std::move(Block_type());
    }

    inline char* ptr_char() {
        return reinterpret_cast<char*>(ptr);
    }

    inline pointer<T> ptr_offset (int offset) {
        return reinterpret_cast<T*>(ptr_char() + offset);
    }

    inline T* nextBlock() {
        return static_cast<T*>(ptr_char() + size);
    }
    
    inline const char* ptr_char() const {
        return static_cast<char*>(ptr);
    }

    inline const T* right_bound() const {
        return static_cast<const T*>(ptr_char() + size);
    }

    void reset() {
        ptr = nullptr;
        size = 0;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    bool operator == (reference_const<Block_type> block) {
        return ptr == block.ptr
            && size == block.size;
    }

    bool operator != (reference_const<Block_type> block) {
        return !(*this == block);
    }
};

template<typename T>
std::ostream& operator << (std::ostream& os, reference_const<Block_type<T>> b) {
    return os << "#" << b.ptr << " (" << b.size << ")";
}

using Block = Block_type<void>;

template<size_t alignment>
size_t align_up_with(size_t size) {
    static_assert((alignment & (alignment - 1)) == 0, "Allignment must be a power of 2"); 
    return (size + alignment - 1) & ~(alignment - 1);
}

inline size_t align_up(size_t size) {
    return align_up_with<4>(size);
}

void block_copy_content(reference_const<Block> lhs, reference_const<Block> rhs) {
    std::memmove(rhs.ptr, lhs.ptr, min(lhs.size, rhs.size));
}

END_NAMESPACE_HAZ_ALLOC

#endif
