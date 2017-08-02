#ifndef __UTILITY
#define __UTILITY

#include <Macro.hpp>
#include <utility>

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

END_NAMESPACE_HAZ

#endif