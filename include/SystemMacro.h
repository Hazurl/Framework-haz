#ifndef __SYSTEMMACRO
#define __SYSTEMMACRO

#define BEG_NAMESPACE_HAZ namespace haz {
#define END_NAMESPACE_HAZ } // namespace haz

#define SAFE_DELETE_ARR(arr) if (arr) { delete [] arr; arr = nullptr; }
#define SAFE_DELETE(ptr) if (ptr) { delete arr; att = nullptr; }

#define HAZ_ASSERT(expr...) if (!(expr)) std::cerr << __FILE__ << ", line " << __LINE__ << ", at" << __PRETTY_FUNCTION__ << std::endl << "Assertion '" << #expr << "' failed" << std::endl;
#define HAZ_ASSERT_MSG(msg, expr...) if (!(expr)) std::cerr << __FILE__ << ", line " << __LINE__ << ", at" << __PRETTY_FUNCTION__ << std::endl << "Assertion '" << #expr << "' failed" << std::endl << msg << std::endl;

#endif