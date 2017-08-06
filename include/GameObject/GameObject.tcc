#ifndef __HAZ_GAMEOBJECT_TCC
#define __HAZ_GAMEOBJECT_TCC

/* Component */
TEMPLATE_T_As_Args
T* GameObject::addComponent(Args... args) {
    std::size_t key = typeid(As).hash_code();
    HAZ_ASSERT_MSG("Component already added !", components.find(key) == components.end());

    auto t = new T(this, args...);
    components[key] = t;
    return t;
}

TEMPLATE_T_As
T* GameObject::addComponent() {
    std::size_t key = typeid(As).hash_code();
    HAZ_ASSERT_MSG("Component already added !", components.find(key) == components.end());

    auto t = new T(this);
    components[key] = t;
    return t;
}

TEMPLATE_T
void GameObject::removeComponent() {
    std::size_t key = typeid(T).hash_code();
    HAZ_ASSERT_MSG("Component not in the gameObject !", components.find(key) != components.end());

    delete components[key];
    components.erase(key);
}

TEMPLATE_T
T* GameObject::getComponent() {
    std::size_t key = typeid(T).hash_code();
    if (components.find(key) == components.end())
        return nullptr;
    else 
        return dynamic_cast<T*>(components[key]);
}

TEMPLATE_T
const T* GameObject::getComponent() const {
    std::size_t key = typeid(T).hash_code();
    if (components.find(key) == components.end())
        return nullptr;
    else 
        return dynamic_cast<T*>(components.at(key));
}

TEMPLATE_T
std::vector<T*> GameObject::getComponentsInChilds() {
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

TEMPLATE_T
std::vector<const T*> GameObject::getComponentsInChilds() const {
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

TEMPLATE_T
T* GameObject::getComponentInChilds() {
    T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;
    
    for (auto* c : childs)
        for (auto* cp : c->getComponentsInChilds<T>())
            if (cp != nullptr)
                return cp;
    
    return nullptr;
}

TEMPLATE_T
const T* GameObject::getComponentInChilds() const {
    const T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;
    
    for (auto* c : childs)
        for (auto* cp : c->getComponentsInChilds<T>())
            if (cp != nullptr)
                return cp;
    
    return nullptr;
}

TEMPLATE_T
T* GameObject::getComponentInParent() {
    T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;

    return parent == nullptr ? nullptr : parent->getComponentInParent<T>();
}

TEMPLATE_T
const T* GameObject::getComponentInParent() const {
    const T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;

    return parent == nullptr ? nullptr : parent->getComponentInParent<T>();
}

#endif