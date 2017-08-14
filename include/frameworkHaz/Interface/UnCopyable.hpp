#ifndef __HAZ_UNCOPYABLE
#define __HAZ_UNCOPYABLE

#include <frameworkHaz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

class UnCopyable {
protected:
	constexpr UnCopyable() = default;
	~UnCopyable() = default;

public:
	UnCopyable(UnCopyable const&) = delete;
	UnCopyable& operator= (UnCopyable const&) = delete;

};

END_NAMESPACE_HAZ

#endif