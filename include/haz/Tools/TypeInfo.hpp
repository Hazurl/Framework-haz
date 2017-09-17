#ifndef __HAZ_TINFO
#define __HAZ_TINFO

#include <haz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

template<typename T>
using type = T;

template<typename T>
using lvalue = T&;

template<typename T>
using lvalue_const = const T&;

template<typename T>
using reference = T&;

template<typename T>
using reference_const = const T&;

template<typename T>
using rvalue = T&&;

template<typename T>
using reference_univ = T&&;

template<typename T>
using pointer = T*;

template<typename T>
using pointer_const = const T*;

END_NAMESPACE_HAZ

#endif