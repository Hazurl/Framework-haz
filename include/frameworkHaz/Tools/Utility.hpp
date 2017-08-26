#ifndef __HAZ_UTILITY
#define __HAZ_UTILITY

#include <frameworkHaz/Tools/Macro.hpp>
#include <utility>
#include <sstream>
#include <memory>
#include <cxxabi.h>

BEG_NAMESPACE_HAZ

template <typename T>
HAZ_FORCE_INLINE T&& move (T& t) {
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
HAZ_FORCE_INLINE const T& min (const T& a, const T& b) {
    return a < b ? a : b;
}
template<typename T>
HAZ_FORCE_INLINE const T& max (const T& a, const T& b) {
    return a > b ? a : b;
}

template<typename T>
HAZ_FORCE_INLINE T clamp (const T& x, const T& a, const T& b) {
    return (x < a ? a : (x > b ? b : x));
}

template<typename T>
HAZ_FORCE_INLINE T lerp (double t, const T& a, const T& b) {
    return a + t * (b - a);
}

template<typename T>
HAZ_FORCE_INLINE T lerpClamp (double t, const T& a, const T& b) {
    return a + clamp<double>(t, 0, 1) * (b - a);
}

template<typename T>
HAZ_FORCE_INLINE T abs (T x) {
    return x < 0 ? -x : x;
}

template<typename T>
HAZ_FORCE_INLINE bool between_ii(const T& x, const T& a, const T& b) {
    return x >= a && x <= b;
}

template<typename T>
HAZ_FORCE_INLINE bool between_xi(const T& x, const T& a, const T& b) {
    return x > a && x <= b;
}

template<typename T>
HAZ_FORCE_INLINE bool between_ix(const T& x, const T& a, const T& b) {
    return x >= a && x < b;
}

template<typename T>
HAZ_FORCE_INLINE bool between_xx(const T& x, const T& a, const T& b) {
    return x > a && x < b;
}

#define TYPE_NAME(x) haz::demangleTypeIdName(typeid(x).name())

HAZ_FORCE_INLINE std::string demangleTypeIdName(const char* name) {
    int status = -4;
    char* res = abi::__cxa_demangle(name, NULL, NULL, &status);
    std::string ret_val(
        (status == 0) ? res : name
    );
    free(res);
    return ret_val;
}

template<typename T>
std::string adress(T* t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

END_NAMESPACE_HAZ

#endif