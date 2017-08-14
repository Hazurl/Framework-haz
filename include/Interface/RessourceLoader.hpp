#ifndef __HAZ_RESSOURCELOADER
#define __HAZ_RESSOURCELOADER

#include <Tools/Macro.hpp>
#include <Interface/Singleton.hpp>
#include <functional>

BEG_NAMESPACE_HAZ

template<typename TType, typename TAllocArg = std::string, typename TKey = TAllocArg, typename TSceneKey = int>
class RessourceLoader : Singleton< RessourceLoader<TType, TAllocArg, TKey, TSceneKey> > {
    typedef Singleton< RessourceLoader<TType, TAllocArg, TKey, TSceneKey> > S;
    friend class Singleton< RessourceLoader<TType, TAllocArg, TKey, TSceneKey> >;

public:

    static void useAllocator(std::function<TType*(TKey const&)> allocator) {
        S::get().allocator = allocator;
    }

    static TType* get(TSceneKey const& scene, TKey const& key) {
        return S::get().ressources[scene][key];
    }

    static TType* load(TSceneKey const& scene, TAllocArg const& arg) {
        return load(scene, arg, arg);
    }

    static TType* load(TSceneKey const& scene, TAllocArg const& arg, TKey const& key) {
        auto& sceneRessources = S::get().ressources[scene];

        if (sceneRessources.find(key) == sceneRessources.end()) {
            return sceneRessources[key] = S::get().allocator(arg);
        }

        return sceneRessources[key];
    }

    static TType* getGlobal(TKey const& key) {
        return S::get().global_ressources[key];
    }

    static TType* loadGlobal(TAllocArg const& arg) {
        return loadGlobal(arg, arg);
    }

    static TType* loadGlobal(TAllocArg const& arg, TKey const& key) {
        if (S::get().global_ressources.find(key) == S::get().global_ressources.end()) {
            return S::get().global_ressources[key] = S::get().allocator(arg);
        }

        return S::get().global_ressources[key];
    }

    static void releaseAll () {
        releaseGlobal();
        releaseAllScenes();
    }

    static void releaseGlobal () {
        for(auto& p : S::get().global_ressources) {
            delete p.second;
        }
        S::get().global_ressources.clear();
    }

    static void releaseScene (TSceneKey const& scene) {
        if (S::get().ressources.find(scene) == S::get().ressources.end())
            return;

        auto& sceneRessources = S::get().ressources[scene];
        for(auto& p : sceneRessources) {
            delete p.second;
        }
        S::get().ressources.erase(scene);
    }

    static void releaseAllScenes () {
        for (auto& s : S::get().ressources) {
            for(auto& p : s.second) {
                delete p.second;
            }
        }
        S::get().ressources.clear();
    }

private:

    RessourceLoader() {}
    ~RessourceLoader() {
        RessourceLoader::releaseAll();
    }

    std::function<TType*(TAllocArg const&)> allocator = [] (TAllocArg const& s) { return new TType(s); };
    std::map<TSceneKey, std::map<TKey, TType*>> ressources;
    std::map<TKey, TType*> global_ressources;
};

END_NAMESPACE_HAZ

#endif
