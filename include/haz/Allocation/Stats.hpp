#ifndef __HAZ_STAT_ALLOC
#define __HAZ_STAT_ALLOC

#include <haz/Tools/Macro.hpp>
#include <haz/Tools/SourceInfo.hpp>
#include <haz/Tools/TypeInfo.hpp>
#include <haz/Tools/EnumFlag.hpp>

#include <haz/Allocation/Afix.hpp>
#include <haz/Allocation/Block.hpp>

#include <chrono>

BEG_NAMESPACE_HAZ_ALLOC

// X(StatList_name, bit_shifting, array_posiion)
#define allocate_count_b            0
#define allocate_ok_count_b         1
#define deallocate_count_b          2
#define deallocate_ok_count_b       3
#define deallocate_all_count_b      4
#define garbage_collector_count_b   5
#define expand_count_b              6
#define expand_ok_count_b           7
#define reallocate_count_b          8
#define reallocate_ok_count_b       9
#define owns_count_b                10
#define owns_ok_count_b             11
#define reallocate_expanded_count_b 12
#define bytes_allocate_b            13
#define bytes_deallocate_b          14
#define bytes_garbage_collected_b   15
#define bytes_expanded_b            16
#define bytes_contracted_b          17
#define bytes_moved_b               18
#define bytes_max_peak_b            19
#define caller_line_b               20
#define caller_func_b               21
#define caller_file_b               22
#define caller_time_b               23
#define caller_size_b               24

#define STATS_BITS_COUNT 20 // we don't take all caller_xxx stats

#define BIT_OF(name) name##_b

#define X_STAT_LIST(X)\
    X(allocate_count)               \
    X(allocate_ok_count)            \
    X(deallocate_count)             \
    X(deallocate_ok_count)          \
    X(deallocate_all_count)         \
    X(garbage_collector_count)      \
    X(expand_count)                 \
    X(expand_ok_count)              \
    X(reallocate_count)             \
    X(reallocate_ok_count)          \
    X(owns_count)                   \
    X(owns_ok_count)                \
    X(reallocate_expanded_count)    \
    X(bytes_allocate)               \
    X(bytes_deallocate)             \
    X(bytes_garbage_collected)      \
    X(bytes_expanded)               \
    X(bytes_contracted)             \
    X(bytes_moved)                  \
    X(bytes_max_peak)
#define X_STAT_CALLER_LIST(X)\
    X(caller_line)                  \
    X(caller_func)                  \
    X(caller_file)                  \
    X(caller_time)                  \
    X(caller_size)

enum class StatList : unsigned int {
#define X(name) name = 1u << BIT_OF(name),
    X_STAT_LIST(X)
    X_STAT_CALLER_LIST(X)
#undef X

    all_count               = ~(~0u << reallocate_count_b),
    bytes_count             = ~(~0u << bytes_max_peak_b) & (~0u << reallocate_count_b),
    caller_all              = ~(~0u << caller_size_b) & (~0u << bytes_max_peak_b),
    all                     = ~0u,
    without_caller          = all & ~caller_all,
};

IMPLM_ENUM_FLAP_OP(StatList);

BEG_NAMESPACE_NESTED_HIDDEN

template<bool has_line> struct Prefix_line { inline void set_line(unsigned int) {} };
template<bool has_func> struct Prefix_func { inline void set_func(const char*) {} };
template<bool has_file> struct Prefix_file { inline void set_file(const char*) {} };
template<bool has_time> struct Prefix_time { inline void set_time() {} };
template<bool has_size> struct Prefix_size { inline void set_size(size_t size) {} inline size_t get_size() { HAZ_ASSERT(false); return 0; } };

template<> struct Prefix_line<true> { unsigned int line;                            inline void set_line(unsigned int line) { this->line = line; } };
template<> struct Prefix_func<true> { const char* func;                             inline void set_func(const char* func) { this->func = func; } };
template<> struct Prefix_file<true> { const char* file;                             inline void set_file(const char* file) { this->file = file; } };
template<> struct Prefix_time<true> { std::chrono::system_clock::time_point time;   inline void set_time() { this->time = std::chrono::system_clock::now(); } };
template<> struct Prefix_size<true> { size_t size;                                  inline void set_size(size_t size) { this->size = size; } 
                                                                                    inline size_t get_size() { return size; } };

template<bool has_line, bool has_func, bool has_file, bool has_time, bool has_size>
struct Prefix : public Prefix_line<has_line>,
                public Prefix_func<has_func>,
                public Prefix_file<has_file>,
                public Prefix_time<has_time>,
                public Prefix_size<has_size> {
    using Self = Prefix<has_line, has_func, has_file, has_time, has_size>;
    Self* next = nullptr;
    Self* prev = nullptr;
};

template<bool b, class A, class B>
struct switch_helper;

template<class A, class B>
struct switch_helper<true, A, B> { using type = A; };
template<class A, class B>
struct switch_helper<false, A, B> { using type = B; };

template<bool b, class A, class B>
using switch_t = typename switch_helper<b, A, B>::type;

END_NAMESPACE_NESTED_HIDDEN

template<typename Alloc, StatList stats = StatList::all>
class Stats {
public:
    static constexpr bool has_caller_stats = stats & StatList::caller_all;

    // either Alloc or Afix<Alloc, Prefix>
    // depends on 'has_caller_stats'
    using TPrefix = NS_HAZ_HIDDEN::Prefix<stats & StatList::caller_line,
                                          stats & StatList::caller_func,
                                          stats & StatList::caller_file,
                                          stats & StatList::caller_time,
                                          stats & StatList::caller_size>;

    using AfixAlloc = Afix<Alloc, TPrefix>;
    using AllocUsed = NS_HAZ_HIDDEN::switch_t<has_caller_stats, AfixAlloc, Alloc>;
    
    AllocUsed allocator;

    unsigned int stats_count[STATS_BITS_COUNT] {0};
    
    TPrefix* root = nullptr;

public:

    using CallerInfo = TPrefix;

#define ADD_OK_STAT(name, amount, cond...) if (stats & StatList::name && (cond)) stats_count[BIT_OF(name)] += amount
#define ADD_STAT(name, amount) ADD_OK_STAT(name, amount, true)
#define UP_STAT(name) ADD_STAT(name, 1)
#define UP_OK_STAT(name, cond...) ADD_OK_STAT(name, 1, cond)

#define X(name) unsigned int name () const { return stats_count[BIT_OF(name)]; }
    X_STAT_LIST(X)
#undef X

    inline Block allocate(size_t size) {
        return allocate(size, {0, "", ""});
    }

    Block allocate(size_t size, SourceInfo source_info) {
        UP_STAT(allocate_count);

        auto block = allocator.allocate(size);
        
        UP_OK_STAT(allocate_ok_count, block);
        ADD_OK_STAT(bytes_allocate, size, block);
        update_max_bytes_peak();

        if (has_caller_stats && block) {
            TPrefix* prefix = AfixAlloc::prefix(block);
            prefix->set_line(source_info.line);
            prefix->set_func(source_info.func);
            prefix->set_file(source_info.file);
            prefix->set_time();
            prefix->set_size(size);
            prefix->next = root;
            if (root) root->prev = prefix;
            root = prefix;
        }
        
        return block;
    }

    void deallocate(reference<Block> block) {
        UP_STAT(deallocate_count);
        size_t size = block.size;
        bool was_root = false;
        
        if (has_caller_stats && block) {
            TPrefix* prefix = AfixAlloc::prefix(block);
            was_root = root == prefix;
            if (prefix->next)
                prefix->next->prev = prefix->prev;
            if (prefix->prev)
                prefix->prev->next = prefix->next;
            if (was_root)
                root = prefix->next;
        }

        allocator.deallocate(block);

        if (has_caller_stats && block) { // restore
            TPrefix* prefix = AfixAlloc::prefix(block);
            if (prefix->next)
                prefix->next->prev = prefix;
            if (prefix->prev)
                prefix->prev->next = prefix;
            if (was_root)
                root = prefix;
        }
        
        UP_OK_STAT(deallocate_ok_count, !block);
        ADD_OK_STAT(bytes_deallocate, size, !block);
    }

    bool owns(reference_const<Block> block) {
        UP_STAT(owns_count);

        bool ok_owns = allocator.owns(block);

        UP_OK_STAT(owns_ok_count, ok_owns);

        return ok_owns;
    }

    bool expand(reference<Block> block, size_t size) {
        UP_STAT(expand_count);
        size_t old_size = block.size;

        bool ok_expand = allocator.expand(block, size);

        if (ok_expand) {
            UP_STAT(expand_ok_count);
            if (old_size > size) {
                ADD_STAT(bytes_deallocate, old_size - size);
                ADD_STAT(bytes_contracted, old_size - size);
            } else {
                ADD_STAT(bytes_allocate, size - old_size);
                ADD_STAT(bytes_expanded, size - old_size);
                update_max_bytes_peak();
            }
        }

        return ok_expand;
    }

    bool reallocate(reference<Block> block, size_t size) {
        UP_STAT(reallocate_count);
        Block old_block = block;
        bool was_root = false;

        if (has_caller_stats) {
            TPrefix* prefix = AfixAlloc::prefix(old_block);
            was_root = prefix == root;
        }
        
        bool ok_reallocate = allocator.reallocate(block, size);

        if (ok_reallocate) {
            UP_STAT(reallocate_ok_count);
            if (old_block.ptr == block.ptr) {
                UP_STAT(reallocate_expanded_count);
                if (old_block.size > size) {
                    ADD_STAT(bytes_deallocate, old_block.size - size);
                    ADD_STAT(bytes_contracted, old_block.size - size);
                } else {
                    ADD_STAT(bytes_allocate, size - old_block.size);
                    ADD_STAT(bytes_expanded, size - old_block.size);
                    update_max_bytes_peak();
                }
            } else {
                ADD_STAT(bytes_deallocate, old_block.size);
                ADD_STAT(bytes_allocate, size);
                ADD_STAT(bytes_moved, min(old_block.size, size));
                update_max_bytes_peak();

                if (has_caller_stats) {
                    TPrefix* prefix = AfixAlloc::prefix(block);
                    if (prefix->next)
                        prefix->next->prev = prefix;
                    if (prefix->prev)
                        prefix->prev->next = prefix;                            
                    if(was_root)
                        root = prefix;
                }
            }

            if (stats & StatList::caller_size) {
                TPrefix* prefix = AfixAlloc::prefix(block);
                prefix->set_size(size);
            }
        }

        return ok_reallocate;        
    }

    // TODO : remove this method or return boolean
    void deallocate_all() {
        UP_STAT(deallocate_all_count);
        allocator.deallocate_all();
        // TODO : root = null ?
    }

    void garbage_collector() {
        UP_STAT(garbage_collector_count);
        if (stats & StatList::caller_size) {
            Block prev;
            for(auto& prefix : *this) {
                if (prev) {
                    size_t size = prev.size;
                    allocator.deallocate(prev); 
                    ADD_OK_STAT(bytes_garbage_collected, size, !prev);
                }

                size_t size = prefix.get_size();
                Block b = AfixAlloc::inner_block(prefix, size);
                prev = b;
            }

            if (prev) {
                size_t size = prev.size;
                allocator.deallocate(prev);
                ADD_OK_STAT(bytes_garbage_collected, size, !prev);
            }
        }
        root = nullptr;
    }

    void print_stats_console () const {
        std::cout << "Stats Allocator : " << std::endl;
#define X(name) if (stats & StatList::name) std::cout << "\t"#name": " << name() << std::endl;
        X_STAT_LIST(X)
#undef X
    }

    template<class Type>
    struct Iterator_t {
        Type* current;
        using Self = Iterator_t<Type>;
        Iterator_t(Type* current) : current(current) {}

        Type& operator * () {
            return *current;
        }

        Type* operator -> () {
            return current;
        }

        Self& operator ++ () {
            if (current != nullptr)
                current = current->next;
            return *this;
        }

        Self operator ++ (int) {
            Self tmp(current);
            ++(*this);
            return tmp;
        }

        Self& operator -- () {
            if (current != nullptr)
                current = current->prev;
            return *this;
        }

        Self operator -- (int) {
            Self tmp(current);
            --(*this);
            return tmp;
        }

        template<typename U>
        bool operator == (Iterator_t<U> const& i) {
            return current == i.current;
        }

        template<typename U>
        bool operator != (Iterator_t<U> const& i) {
            return !(*this == i);
        }
    };

    using iterator = Iterator_t<TPrefix>;
    using iterator_const = Iterator_t<const TPrefix>;

    iterator begin() {
        return iterator(root);
    }

    iterator end() {
        return iterator(nullptr);
    }

    iterator_const begin() const {
        return iterator_const(root);
    }

    iterator_const end() const {
        return iterator_const(nullptr);
    }

private:

    void update_max_bytes_peak() {
        unsigned int actual_peak = stats_count[bytes_allocate_b] - stats_count[bytes_deallocate_b];
        unsigned int& peak = stats_count[bytes_max_peak_b];
        if (actual_peak > peak)
            peak = actual_peak;
    }

};

#undef ADD_OK_STAT
#undef ADD_STAT
#undef UP_STAT
#undef UP_OK_STAT

#undef X_STAT_CALLER_LIST
#undef X_STAT_LIST
#undef STATS_BITS_COUNT
#undef BIT_OF

#undef allocate_count_b
#undef allocate_ok_count_b
#undef deallocate_count_b
#undef deallocate_ok_count_b
#undef deallocate_all_count_b
#undef expand_count_b
#undef expand_ok_count_b
#undef reallocate_count_b
#undef reallocate_ok_count_b
#undef owns_count_b
#undef owns_ok_count_b
#undef reallocate_expanded_count_b
#undef bytes_allocate_b
#undef bytes_deallocate_b
#undef bytes_expanded_b
#undef bytes_contracted_b
#undef bytes_moved_b
#undef bytes_max_peak_b
#undef caller_line_b
#undef caller_func_b
#undef caller_file_b
#undef caller_time_b
#undef caller_size_b

END_NAMESPACE_HAZ_ALLOC

#endif