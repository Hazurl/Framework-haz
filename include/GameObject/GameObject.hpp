#ifndef __HAZ_GAMEOBJECT
#define __HAZ_GAMEOBJECT

#include <GameObject/Component.hpp>
#include <Macro.hpp>
#include <Utility.hpp>
#include <map>

BEG_NAMESPACE_HAZ

class GameObject {
public:
    GameObject() : components({}) {}

    virtual ~GameObject() {
        for (auto& p : components) {
            std::cout << "Delete : " << TYPE_NAME(p.second) << std::endl;
            delete p.second;
        }
        components.clear();
    }

    GameObject(GameObject const& go) {
        *this = go;
    }

    GameObject& operator=(GameObject go) {
        swap(*this, go);
        return *this;
    }

    static void swap(GameObject& a, GameObject& b) {
        haz::swap(a.components, b.components);
    }

    /* Component */
    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type, typename ...Args>
    void addComponent(Args... args) {
        std::string key = typeid(T).name();
        HAZ_ASSERT_MSG("Component already added !", components.find(key) == components.end());

        components[key] = new T(args...);
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    void addComponent() {
        std::string key = typeid(T).name();
        HAZ_ASSERT_MSG("Component already added !", components.find(key) == components.end());

        components[key] = new T();
    }

    

protected:

private:
    std::map<std::string, Component*> components;
};

END_NAMESPACE_HAZ

#endif