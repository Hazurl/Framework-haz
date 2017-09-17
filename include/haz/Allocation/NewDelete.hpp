#ifndef __HAZ_NEWDELETE
#define __HAZ_NEWDELETE

#include <haz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ_ALLOC

class Block;

class NewDelete {
public:
    
    Block allocate(size_t size);
    void deallocate(reference<Block> block);
    bool owns(reference_const<Block>) const;
    bool reallocate(reference<Block> block, size_t size);
    bool expand(reference<Block> block, size_t size);
    void deallocate_all();

};

END_NAMESPACE_HAZ_ALLOC

#endif
