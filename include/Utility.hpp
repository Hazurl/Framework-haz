#ifndef __HAZ_UTILITY
#define __HAZ_UTILITY

#include <Macro.hpp>
#include <utility>
#include <memory>
#include <cxxabi.h>

BEG_NAMESPACE_HAZ

template <typename T>
inline T&& move (T& t) {
    return static_cast<typename std::remove_reference<T>::type&&>(t); // TODO : re-do these structure
}

template <typename T>
void swap(T& l, T& r) {
    T tmp = move(l);
    l = move(r);
    r = move(tmp);
}

template<typename T>
void arrayCopy(const T* from, T* to, unsigned int size) {
    for(unsigned int _ = 0; _ < size; ++_, ++from, ++to)
        *to = *from;
}

template<typename T>
void arrayCopyR(const T* from, T* to, unsigned int size) {
    for(unsigned int _ = 0; _ < size; ++_, --from, --to)
        *to = *from;
}

template<typename T>
inline T& min (T& a, T& b) {
    return a < b ? a : b;
}

template<typename T>
inline const T& min (const T& a, const T& b) {
    return a < b ? a : b;
}

template<typename T>
inline T& max (T& a, T& b) {
    return a > b ? a : b;
}

template<typename T>
inline const T& max (const T& a, const T& b) {
    return a > b ? a : b;
}

#define TYPE_NAME(x) haz::demangleTypeIdName(typeid(x).name())

inline std::string demangleTypeIdName(const char* name) {
    int status = -4;
    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);
    std::string ret_val(
        (status == 0) ? res : name
    );
    free(res);
    return ret_val;
}

END_NAMESPACE_HAZ

#endif