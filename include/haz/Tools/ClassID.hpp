#ifndef __HAZ_CLASS_ID
#define __HAZ_CLASS_ID

#include <haz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ

BEG_NAMESPACE_NESTED_HIDDEN

class ClassID_helper {
public:
    static int id;
};


END_NAMESPACE_NESTED_HIDDEN

template<typename ...Args>
class ClassID {
public:
    inline static int id() {
        static int _id = NS_HAZ_HIDDEN::ClassID_helper::id++;
        return _id;
    }
};

END_NAMESPACE_HAZ

#endif