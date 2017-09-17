#ifndef __HAZ_SUBSCRIBER
#define __HAZ_SUBSCRIBER

#include <haz/Tools/Macro.hpp>
#include <unordered_set>
#include <vector>

BEG_NAMESPACE_HAZ

template<typename T>
class Subscriber {
public:

    static std::vector<T*> get () {
        return std::vector<T*>(set.begin(), set.end());
    }

protected:
    Subscriber() {
        subscribe();
    }

    virtual ~Subscriber() {
        unsubscribe();
    }

    void subscribe () {
        set.insert(static_cast<T*>(this));
    }

    void unsubscribe () {
        set.erase(static_cast<T*>(this));
    }

private:

    static std::unordered_set<T*> set;

};

template<typename T>
std::unordered_set<T*> Subscriber<T>::set;

END_NAMESPACE_HAZ

#endif
