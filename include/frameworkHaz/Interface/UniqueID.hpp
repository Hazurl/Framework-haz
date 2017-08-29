#ifndef __HAZ_IDABLE
#define __HAZ_IDABLE

#include <frameworkHaz/Tools/Macro.hpp>
#include <cstdint>

BEG_NAMESPACE_HAZ

class UniqueID {
public:
    UniqueID();

    const std::uintptr_t id;

private:
};

END_NAMESPACE_HAZ

#endif
