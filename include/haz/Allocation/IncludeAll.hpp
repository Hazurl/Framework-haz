#ifndef __HAZ_INCLUDE_ALL_ALLOCATORS
#define __HAZ_INCLUDE_ALL_ALLOCATORS

/*
    Allocators inspired from Andrei Alexandrescu
    Composable policy based allocators

    Block : 
        represents a memory region
        * ptr : location of memory
        * size : numbers of bytes allocated

    Composable Allocators : 
        API :
            * Block allocate( size_t )
                return a block of memory at the right location
                if it cannot allocate, it will returns a null block (ptr = nullptr, size = 0)
            * void deallocate( Block& )
                deallocate the block and set the block to null block
                if it cannot, the block is unchanged
            * bool owns( Block )
                return true if the block can be deallocate by this
            * bool reallocate( Block&, size )
                principaly deallocate and allocate a new block with the new size, and copy the memory between both location
                if it cannot allocate a new block or cannot deallocate the block, the block is leave unchanged
                return true if the block has been reallocate successfuly
            * bool expand( Block&, size )
                same as reallocate but it doesn't change the location of Block::ptr
            * void deallocate_all()
                free all memory stored by this allocator
                depends on the allocator

    Branch < limit, under_allocator_t, above_allocator_t > :
        if the size to allocate is above 'limit', the allocation is perform by 'above_allocator_t' else by 'under_allocator_t'

    Fallback < main_allocator_t, emergency_allocator_t > :
        try to allocate with 'main_allocator_t', if not use 'emergency_allocator_t'

    NewDelete :
        use 'new' operator to allocate
        use 'delete' operator to deallocate
    
    Stack < size > :
        put block on top of a stack
        deallocate must be called in reverse order of allocate order; i.e. : ALLOC a -> b -> c; DALLOC c -> b -> a

    FreeList < allocator_t, size_min, size_max > :
        recycle every block deallocated which size is in range ]size_min, size_max]

    Affix < allocator_t, prefix_t, sufix_t > :
        add a prefix_t at the front of every block
        add a sufix_t at the end of every block 
        the block still point to the correct space
            i.e. : [ PREFIX | BLOCK | SUFIX ], Block::ptr point to the start of "BLOCK"
        sufix_t and prefix_t must have a public constructor with no arguments
        to access the block own by sufix_t and prefix_t, use corresponding function : block_to_sufix, block_to_prefix

    Stats < allocator_t > :
        Register general stats
    
*/

#include <haz/Allocation/Block.hpp>

#include <haz/Allocation/Branch.hpp>
#include <haz/Allocation/Fallback.hpp>

#include <haz/Allocation/NewDelete.hpp>
#include <haz/Allocation/Stack.hpp>
#include <haz/Allocation/FreeList.hpp>
#include <haz/Allocation/Afix.hpp>
#include <haz/Allocation/Stats.hpp>

#include <haz/Allocation/FixedType.hpp>

#endif