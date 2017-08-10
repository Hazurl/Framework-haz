#ifndef __HAZ_MACRO
#define __HAZ_MACRO

#include <iostream>

#define NS_HAZ haz
#define USING_NS_HAZ using namespace NS_HAZ;
#define BEG_NAMESPACE_HAZ namespace NS_HAZ {
#define END_NAMESPACE_HAZ }

#define NS_HAZ_HIDDEN __hide
#define USING_NS_HAZ_HIDDEN using namespace NS_HAZ::NS_HAZ_HIDDEN;
#define BEG_NAMESPACE_HAZ_HIDDEN BEG_NAMESPACE_HAZ namespace NS_HAZ_HIDDEN {
#define END_NAMESPACE_HAZ_HIDDEN } END_NAMESPACE_HAZ 

#define NS_HAZ_2D _2D
#define USING_NS_HAZ_2D using namespace NS_HAZ::NS_HAZ_2D;
#define BEG_NAMESPACE_HAZ_2D BEG_NAMESPACE_HAZ namespace NS_HAZ_2D {
#define END_NAMESPACE_HAZ_2D } END_NAMESPACE_HAZ 

#define NS_HAZ_COLLISION Collision
#define USING_NS_HAZ_COLLISION using namespace NS_HAZ::NS_HAZ_2D::NS_HAZ_COLLISION;
#define BEG_NAMESPACE_HAZ_COLLISION BEG_NAMESPACE_HAZ_2D namespace NS_HAZ_COLLISION {
#define END_NAMESPACE_HAZ_COLLISION } END_NAMESPACE_HAZ_2D 

#define HAZ_INLINE inline
#define HAZ_FORCE_INLINE HAZ_INLINE 
//__attribute__((always_inline)) 

#define SAFE_DELETE_ARR(arr) if (arr) { delete [] arr; arr = nullptr; }
#define SAFE_DELETE(ptr) if (ptr) { delete arr; att = nullptr; }

#define __NOTHING ((void) 0)
#define __NOTHING_F(...) ((void) 0)

#ifdef RELEASE_MODE
#   define HAZ_ASSERT(expr) __NOTHING;
#   define HAZ_ASSERT_MSG(msg, expr) __NOTHING;
#else
#   define HAZ_ASSERT(expr) if (!(expr)) { std::cerr << __FILE__ << ", line " << __LINE__ << ", at" << __PRETTY_FUNCTION__ << std::endl << "Assertion '" << #expr << "' failed" << std::endl; exit(1); }
#   define HAZ_ASSERT_MSG(msg, expr) if (!(expr)) { std::cerr << __FILE__ << ", line " << __LINE__ << ", at" << __PRETTY_FUNCTION__ << std::endl << "Assertion '" << #expr << "' failed" << std::endl << msg << std::endl; exit(1); }
#endif

#define _LOG(x...) std::cout << "From " __PRETTY_FUNCTION__ ", at " __LINE__ " (" __FILE__ ") : " << std::endl << x << std::endl
#define _WRITE(x...) std::cout << x << std::endl

#define LOG _LOG
#define WRITE _WRITE

#define HAZ_TEMPLATE_MUST_BE_BASE_OF(base, type...) static_assert(std::is_base_of<base, type>::value, "This template " #type " must inherit from " #base);

#define CALL_X_TIMES(x) for (int __i__ = x; __i__ > 0; __i__--)
#define MERGE(a, b) a##b
#define UNIQUE_NAME_(name, line) MERGE(name, line)
#define UNIQUE_NAME(name) UNIQUE_NAME_(name, __LINE__)

#endif