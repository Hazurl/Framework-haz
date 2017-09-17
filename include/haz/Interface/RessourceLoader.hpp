#ifndef __HAZ_RESSOURCELOADER
#define __HAZ_RESSOURCELOADER

#include <haz/Tools/Macro.hpp>
#include <haz/Interface/Singleton.hpp>
#include <haz/Interface/Allocator.hpp>
#include <functional>

BEG_NAMESPACE_HAZ

template<typename TType, typename TAllocArg = std::string, typename TKey = TAllocArg, typename TSceneKey = int, typename TAllocator = DefaultAllocator<TType, TAllocArg>>
class RessourceLoader : Singleton< RessourceLoader<TType, TAllocArg, TKey, TSceneKey, TAllocator> > {
    typedef Singleton< RessourceLoader<TType, TAllocArg, TKey, TSceneKey, TAllocator> > S;
    friend class Singleton< RessourceLoader<TType, TAllocArg, TKey, TSceneKey, TAllocator> >;

public:

    static void setDefault(TAllocArg const& arg) {
        if (S::get().default_type != nullptr) {
            delete S::get().default_type;
        }

        S::get().default_type =  S::get().allocator.allocate(arg);
    }

    static TType* getDefault() {
        return S::get().default_type;
    }

    static TType* get(TSceneKey const& scene, TKey const& key) {
        try {
            return S::get().ressources[scene][key];
        } catch(...) {
            if (S::get().default_type != nullptr) {
                return S::get().default_type;
            }
            throw;
        }
    }

    template<typename K = TKey, typename A = TAllocArg>
    static typename std::enable_if<std::is_same<K, A>::value, TType*>::type load(TSceneKey const& scene, TAllocArg const& arg) {
        return load(scene, arg, arg);
    }

    template<typename K = TKey, typename A = TAllocArg>
    static typename std::enable_if<!std::is_same<K, A>::value, TType*>::type load(TSceneKey const& scene, TAllocArg const& arg) {
        HAZ_STATIC_ASSERT_MSG("Use load(scene, key, path) and not only load(scene, key_and_path) when the key and the argument is different !", (std::is_same<K, A>::value));
    }

    static TType* load(TSceneKey const& scene, TAllocArg const& arg, TKey const& key) {
        auto& sceneRessources = S::get().ressources[scene];

        if (sceneRessources.find(key) == sceneRessources.end()) {
            return sceneRessources[key] = S::get().allocator.allocate(arg);
        }

        return sceneRessources[key];
    }

    static TType* getGlobal(TKey const& key) {
        try {
            return S::get().global_ressources[key];
        } catch(...) {
            if (S::get().default_type != nullptr) {
                return S::get().default_type;
            }
            throw;
        }
    }

    template<typename K = TKey, typename A = TAllocArg>
    static typename std::enable_if<std::is_same<K, A>::value, TType*>::type loadGlobal(TAllocArg const& arg) {
        return loadGlobal(arg, arg);
    }

    template<typename K = TKey, typename A = TAllocArg>
    static typename std::enable_if<!std::is_same<K, A>::value, TType*>::type loadGlobal(TAllocArg const& arg) {
        HAZ_STATIC_ASSERT_MSG("Use loadGlobal(key, path) and not only loadGlobal(key_and_path) when the key and the argument is different !", (std::is_same<K, A>::value));
    }

    static TType* loadGlobal(TAllocArg const& arg, TKey const& key) {
        if (S::get().global_ressources.find(key) == S::get().global_ressources.end()) {
            return S::get().global_ressources[key] = S::get().allocator.allocate(arg);
        }

        return S::get().global_ressources[key];
    }

    static void releaseAll () {
        releaseGlobal();
        releaseAllScenes();

        if (S::get().default_type != nullptr) {
            delete S::get().default_type;
        }
    }

    static void releaseGlobal () {
        for(auto& p : S::get().global_ressources) {
            S::get().allocator.deallocate(p.second);
        }
        S::get().global_ressources.clear();
    }

    static void releaseScene (TSceneKey const& scene) {
        if (S::get().ressources.find(scene) == S::get().ressources.end())
            return;

        auto& sceneRessources = S::get().ressources[scene];
        for(auto& p : sceneRessources) {
            S::get().allocator.deallocate(p.second);
        }
        S::get().ressources.erase(scene);
    }

    static void releaseAllScenes () {
        for (auto& s : S::get().ressources) {
            for(auto& p : s.second) {
                S::get().allocator.deallocate(p.second);
            }
        }
        S::get().ressources.clear();
    }

private:

    RessourceLoader() {}
    ~RessourceLoader() {
        RessourceLoader::releaseAll();
    }

    std::map<TSceneKey, std::map<TKey, TType*>> ressources;
    std::map<TKey, TType*> global_ressources;

    TType* default_type = nullptr;

    TAllocator allocator;
};

END_NAMESPACE_HAZ

#endif
