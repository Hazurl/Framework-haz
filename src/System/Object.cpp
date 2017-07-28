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

END_NAMESPACE_HAZ