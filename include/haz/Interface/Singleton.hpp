#ifndef __HAZ_SINGLETON
#define __HAZ_SINGLETON

#include <haz/Tools/Macro.hpp>
#include <haz/Interface/UnCopyable.hpp>

BEG_NAMESPACE_HAZ

/*
 * The Child class must write "friend class Singleton<T>"
 */
template<typename T>
class Singleton : public UnCopyable {
public:
	HAZ_FORCE_INLINE static T& get() {
        static T instance;
        return instance;
    }

private:

};

END_NAMESPACE_HAZ

#endif