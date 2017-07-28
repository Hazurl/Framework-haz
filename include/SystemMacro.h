#ifndef __SYSTEMMACRO
#define __SYSTEMMACRO

#define BEG_NAMESPACE_HAZ namespace haz {
#define END_NAMESPACE_HAZ } // namespace haz

#define SAFE_DELETE_ARR(arr) if (arr) { delete [] arr; arr = nullptr; }
#define SAFE_DELETE(ptr) if (ptr) { delete arr; att = nullptr; }

#endif