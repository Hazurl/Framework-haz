#ifndef __HAZ_MACRO
#define __HAZ_MACRO

#include <iostream>

#define BEG_NAMESPACE_HAZ namespace haz {
#define END_NAMESPACE_HAZ }

#define BEG_NAMESPACE_HAZ_HIDDEN BEG_NAMESPACE_HAZ namespace __hide {
#define END_NAMESPACE_HAZ_HIDDEN } END_NAMESPACE_HAZ 

#define BEG_NAMESPACE_HAZ_GEOM2 BEG_NAMESPACE_HAZ namespace Geometry2 {
#define END_NAMESPACE_HAZ_GEOM2 } END_NAMESPACE_HAZ 

#define SAFE_DELETE_ARR(arr) if (arr) { delete [] arr; arr = nullptr; }
#define SAFE_DELETE(ptr) if (ptr) { delete arr; att = nullptr; }

#ifdef RELEASE_MODE
#   define HAZ_ASSERT(expr) ((void)0);
#   define HAZ_ASSERT_MSG(msg, expr) ((void)0);
#else
#   define HAZ_ASSERT(expr) if (!(expr)) { std::cerr << __FILE__ << ", line " << __LINE__ << ", at" << __PRETTY_FUNCTION__ << std::endl << "Assertion '" << #expr << "' failed" << std::endl; exit(1); }
#   define HAZ_ASSERT_MSG(msg, expr) if (!(expr)) { std::cerr << __FILE__ << ", line " << __LINE__ << ", at" << __PRETTY_FUNCTION__ << std::endl << "Assertion '" << #expr << "' failed" << std::endl << msg << std::endl; exit(1); }
#endif

#define HAZ_TEMPLATE_MUST_BE_BASE_OF(base, type...) static_assert(std::is_base_of<base, type>::value, "This template " #type " must inherit from " #base);

#define CALL_X_TIMES(x) for (int __i__ = x; __i__ > 0; __i__--)
#define MERGE(a, b) a##b
#define UNIQUE_NAME_(name, line) MERGE(name, line)
#define UNIQUE_NAME(name) UNIQUE_NAME_(name, __LINE__)

#endif