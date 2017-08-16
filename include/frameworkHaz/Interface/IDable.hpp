#ifndef __HAZ_IDABLE
#define __HAZ_IDABLE

#include <frameworkHaz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

class IDable {
public:
    typedef long ID_t;

    IDable() ;

    const ID_t id;

private:
    static ID_t next;
};

END_NAMESPACE_HAZ

#endif
