#include <frameworkHaz/Interface/IDable.hpp>

BEG_NAMESPACE_HAZ

IDable::ID_t IDable::next = 0;

IDable::IDable() : id(IDable::next++) {

}

END_NAMESPACE_HAZ