#include <haz/Interface/UniqueID.hpp>

BEG_NAMESPACE_HAZ

UniqueID::UniqueID() : id(reinterpret_cast<std::uintptr_t>(this)) {}

END_NAMESPACE_HAZ