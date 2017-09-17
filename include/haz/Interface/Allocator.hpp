#ifndef __HAZ_ALLOCATOR
#define __HAZ_ALLOCATOR

#include <haz/Tools/Macro.hpp>
#include <haz/Tools/TypeInfo.hpp>
#include <haz/Tools/Utility.hpp>
#include <unordered_set>

BEG_NAMESPACE_HAZ

template<typename TType, typename ...TArgs>
class Allocator {
public:
    virtual TType* allocate(TArgs ... args) = 0;
    virtual void deallocate(TType* t) = 0;
};

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


BEG_NAMESPACE_HAZ_EXP

template<typename T>
class IAllocator {
public:
    using type = T;

    virtual pointer<T> allocate     (unsigned int size) = 0;
    virtual pointer<T> alloc_constr (unsigned int size)                             { auto ptr = allocate(size); for(; size; size--) construct(ptr + (size - 1)); return ptr; }
    virtual pointer<T> alloc_constr (unsigned int size, reference_const<T> copy)    { auto ptr = allocate(size); for(; size; size--) construct(ptr + (size - 1), copy); return ptr; }
    virtual void construct          (pointer<T> ptr) = 0;
    virtual void construct          (pointer<T> ptr, reference_const<T> copy) = 0;

    virtual void deallocate         (pointer<T> ptr, unsigned int size) = 0;
    virtual void dealloc_del        (pointer<T> ptr, unsigned int size)             { for(; size; size--) destroy(ptr + (size - 1)); deallocate(ptr, size); }
    virtual void destroy            (pointer<T> ptr) = 0;
};

template<typename T>
class AllocatorNewDelete : public IAllocator<T> {
public:
    pointer<T> allocate(unsigned int size) override {
        return 
            reinterpret_cast<pointer<T>>(
                ::operator new (
                    size * sizeof(T)
                )
            );
    }

    void deallocate(pointer<T> ptr, unsigned int /* size */) override {
        delete ptr;
    }

    virtual void construct(pointer<T> ptr) override {
        new (ptr) T();
    }

    virtual void construct(pointer<T> ptr, reference_const<T> copy) override {
        new (ptr) T(copy);
    }

    virtual void destroy(pointer<T> ptr) override {
        ptr->~T();
    }
};

template<typename T, template<typename> typename AllocUsed = AllocatorNewDelete>
class AllocatorTracking : public IAllocator<T> {
    AllocUsed<T> alloc;
public:

    pointer<T> allocate(unsigned int size) override {
        auto ptr = alloc.allocate(size);
        allocated += size;
        return ptr;
    }

    void deallocate(pointer<T> ptr, unsigned int size) override {
        alloc.deallocate(ptr, size);
        deallocated += size;
    }

    virtual void construct(pointer<T> ptr) override {
        alloc.construct(ptr);
    }

    virtual void construct(pointer<T> ptr, reference_const<T> copy) override{
        alloc.construct(ptr, copy);
    }

    virtual void destroy(pointer<T> ptr) override {
        alloc.destroy(ptr);
    }

    int num_allocated   () const { return allocated; }
    int num_deallocated () const { return deallocated; }

private:
    int allocated = 0;
    int deallocated = 0;
};

template<typename T, template<typename> typename AllocUsed = AllocatorNewDelete>
class AllocatorSafeTracking : public IAllocator<T> {
    AllocUsed<T> alloc;

    struct Memory {
        pointer<T> ptr;
        unsigned int size;

        inline bool operator == (reference_const<Memory> rhs) const {
            return ptr == rhs.ptr && size == rhs.size;
        }
    };

    struct HashMemory {
        std::size_t operator () (reference_const<Memory> m) const {
            return 
                reinterpret_cast<std::size_t>(m.ptr) ^ 
                static_cast<std::size_t>(m.size);
        }
    };

public:

    pointer<T> allocate(unsigned int size) override {
        auto ptr = alloc.allocate(size);
        memory.insert( { ptr, size } );
        allocated += size;
        return ptr;
    }

    void deallocate(pointer<T> ptr, unsigned int size) override {
        alloc.deallocate(ptr, size);
        memory.erase( { ptr, size } );
        deallocated += size;
    }

    virtual void construct(pointer<T> ptr) override {
        alloc.construct(ptr);
    }

    virtual void construct(pointer<T> ptr, reference_const<T> copy) override{
        alloc.construct(ptr, copy);
    }

    virtual void destroy(pointer<T> ptr) override {
        alloc.destroy(ptr);
    }

    virtual pointer<T> alloc_constr(unsigned int size) override {
        auto ptr = alloc.alloc_constr(size);
        memory.insert( { ptr, size } );
        allocated += size;
        return ptr;
    }

    virtual pointer<T> alloc_constr(unsigned int size, reference_const<T> copy) override {
        auto ptr = alloc.alloc_constr(size, copy);
        memory.insert( { ptr, size } );
        allocated += size;
        return ptr;
    }

    virtual void dealloc_del(pointer<T> ptr, unsigned int size) override {
        alloc.dealloc_del(ptr, size);
        memory.erase( { ptr, size } );
        deallocated += size;
    }

    int num_allocated   () const { return allocated; }
    int num_deallocated () const { return deallocated; }
    int num_block_leaked() const { return memory.size(); }

    void deallocate_all () {
        for(auto& m : memory) {
            alloc.deallocate(m.ptr, m.size);
        }
        deallocated = allocated;
        memory.clear();
    }

private:

    std::unordered_set<Memory, HashMemory> memory;
    int allocated = 0;
    int deallocated = 0;

};

struct X { };

template<typename AllocToTest = AllocatorSafeTracking<X>>
void test_allocator() {
    std::cout << "Begin test_allocator_new_delete..." << std::endl;
    AllocToTest a;
    for(int i = 1; i < 10; i++) {
        auto x = a.alloc_constr(i);
        //a.construct(x);
        //a.destroy(x);
        //a.dealloc_del(x, i);
    }

    std::cout << a.num_allocated() - a.num_deallocated() << " leaked in " << a.num_block_leaked() << " blocks" << std::endl;
    a.deallocate_all();
    std::cout << a.num_allocated() - a.num_deallocated() << " leaked in " << a.num_block_leaked() << " blocks" << std::endl;
    
    std::cout << "End..." << std::endl;
}

END_NAMESPACE_HAZ_EXP

#endif
