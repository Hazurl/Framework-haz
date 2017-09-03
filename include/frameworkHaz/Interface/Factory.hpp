#ifndef __HAZ_FACTORY
#define __HAZ_FACTORY

#include <frameworkHaz/Tools/Macro.hpp>
#include <map>
#include <string>

#include <frameworkHaz/Interface/Singleton.hpp>
#include <frameworkHaz/Interface/Allocator.hpp>

BEG_NAMESPACE_HAZ

template<typename O, typename K = std::string, typename Alloc = DefaultAllocator<O, O>>
class Factory : private Singleton<Factory<O, K, Alloc>> {
    typedef Factory<O, K, Alloc> Me;
    typedef Singleton<Me> Base;
    typedef std::map<K, O*> Map;
    typedef std::pair<K, O*> Pair;

    friend class Singleton<Me>;

    static Alloc allocator;

    Factory() : objects({}) {}

	~Factory() {
        for (Pair p : objects)
            allocator.deallocate(p.second);
        objects.clear();
    }

public:

    static void registerObject(K const& key, O* obj) {
        typename Map::iterator it = Base::get().objects.find(key);
        if (it != Base::get().objects.end())
            allocator.deallocate(it->second);

        Base::get().objects[key] = obj;
    }

    static O* createObject(K const& key) {
        return allocator.allocate(*Base::get().objects[key]);
    }

    static O* original(K const& key) {
        return Base::get().objects[key];
    }

private:
    Map objects = {};
};

END_NAMESPACE_HAZ

#endif