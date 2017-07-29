#include <System/Object.hpp>

BEG_NAMESPACE_HAZ

Object::~Object () {

}

TypeInfo Object::getType() const {
    return { demangle(typeid(*this).name()) };
}

const Object::TString Object::demangle(const char* name) {
    int status = -4;
    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);
    Object::TString ret_val(
        (status == 0) ? res : name
    );
    free(res);
    return ret_val;
}

Object::TString Object::to_string() const {
    return getType().name + std::to_string(hash());
}

std::ostream& operator<< (std::ostream& os, Object const& o) {
    os << o.to_string();
    return os;
}

END_NAMESPACE_HAZ