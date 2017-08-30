#ifndef __HAZ_FACTORY
#define __HAZ_FACTORY

#include <frameworkHaz/Tools/Macro.hpp>
#include <map>
#include <string>

#include <frameworkHaz/Interface/Singleton.hpp>

BEG_NAMESPACE_HAZ

template<typename O, typename K = std::string>
class Factory : private Singleton<Factory<O, K>> {
    typedef Factory<O, K> Me;
    typedef Singleton<Me> Base;
    typedef std::map<K, O*> Map;
    typedef std::pair<K, O*> Pair;

    friend class Singleton<Me>;

    Factory() : objects({}) {}

	~Factory() {
        for (Pair p : objects)
            delete p.second;
        objects.clear();
    }

public:

    static void registerObject(K const& key, O* obj) {
        typename Map::iterator it = Base::get().objects.find(key);
        if (it != Base::get().objects.end())
            delete Base::get().objects[key];

        Base::get().objects[key] = obj;
    }

    static O* createObject(K const& key) {
        return new O(*Base::get().objects.at(key));
    }

    static O* original(K const& key) {
        return Base::get().objects.at(key);
    }

private:
    Map objects = {};
};

END_NAMESPACE_HAZ

#endif