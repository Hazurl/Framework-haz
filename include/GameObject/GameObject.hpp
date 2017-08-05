#ifndef __HAZ_GAMEOBJECT
#define __HAZ_GAMEOBJECT

#include <GameObject/Component.hpp>
#include <Macro.hpp>
#include <Utility.hpp>
#include <map>
#include <vector>
#include <algorithm>

BEG_NAMESPACE_HAZ

class GameObject {
public:
    GameObject() : components({}) {}

    virtual ~GameObject() {
        for (auto& p : components) {
            std::cout << "Delete : " << TYPE_NAME(*p.second) << std::endl;
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
    T* addComponent(Args... args) {
        std::size_t key = typeid(T).hash_code();
        HAZ_ASSERT_MSG("Component already added !", components.find(key) == components.end());

        auto t = new T(args...);
        t->go = this;
        components[key] = t;
        return t;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    T* addComponent() {
        std::size_t key = typeid(T).hash_code();
        HAZ_ASSERT_MSG("Component already added !", components.find(key) == components.end());

        auto t = new T();
        t->go = this;
        components[key] = t;
        return t;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    T* getComponent() {
        std::size_t key = typeid(T).hash_code();
        if (components.find(key) == components.end())
            return nullptr;
        else 
            return dynamic_cast<T*>(components[key]);
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    const T* getComponent() const {
        std::size_t key = typeid(T).hash_code();
        if (components.find(key) == components.end())
            return nullptr;
        else 
            return dynamic_cast<T*>(components.at(key));
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    std::vector<T*> getComponentsInChilds() {
        std::vector<T*> v = {};
        T* comp = getComponent<T>();
        if (comp != nullptr)
            v.push_back(comp);
        
        for (auto* c : childs) {
            for (auto* cp : c->getComponentsInChilds<T>())
                v.push_back(cp);
        }
        return v;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    std::vector<const T*> getComponentsInChilds() const {
        std::vector<const T*> v = {};
        const T* comp = getComponent<T>();
        if (comp != nullptr)
            v.push_back(comp);
        
        for (auto* c : childs) {
            for (auto* cp : c->getComponentsInChilds<T>())
                v.push_back(cp);
        }
        return v;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    T* getComponentInChilds() {
        T* comp = getComponent<T>();
        if (comp != nullptr)
            return comp;
        
        for (auto* c : childs)
            for (auto* cp : c->getComponentsInChilds<T>())
                if (cp != nullptr)
                    return cp;
        
        return nullptr;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    const T* getComponentInChilds() const {
        const T* comp = getComponent<T>();
        if (comp != nullptr)
            return comp;
        
        for (auto* c : childs)
            for (auto* cp : c->getComponentsInChilds<T>())
                if (cp != nullptr)
                    return cp;
        
        return nullptr;
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    T* getComponentInParent() {
        T* comp = getComponent<T>();
        if (comp != nullptr)
            return comp;

        return parent == nullptr ? nullptr : parent->getComponentInParent<T>();
    }

    template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
    const T* getComponentInParent() const {
        const T* comp = getComponent<T>();
        if (comp != nullptr)
            return comp;

        return parent == nullptr ? nullptr : parent->getComponentInParent<T>();
    }

    void setParent(GameObject* go) {
        if (parent != nullptr) {
            auto it = std::find(parent->childs.begin(), parent->childs.end(), this);
            if (it != parent->childs.end())
                parent->childs.erase(it);
        }

        if (go != nullptr)
            go->childs.push_back(this);
        parent = go;
    }


    void addChild(GameObject* go) {
        if (go != nullptr)
            go->setParent(this);
    }

    std::string to_string() const {
        return name;
    }

    void setName(std::string const& n) {
        name = n;
    }

    std::string getTag() const {
        return tag;
    }

    void setTag(std::string const& t) {
        tag = t;
    }

protected:

private:
    std::map<std::size_t, Component*> components;

    GameObject* parent = nullptr;
    std::vector<GameObject*> childs = {};

    std::string name;
    std::string tag;
};

END_NAMESPACE_HAZ

#endif