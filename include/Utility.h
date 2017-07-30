#ifndef __UTILITY
#define __UTILITY

#include <Macro.h>
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

END_NAMESPACE_HAZ

#endif