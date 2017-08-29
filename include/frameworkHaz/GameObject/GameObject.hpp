#ifndef __HAZ_GAMEOBJECT
#define __HAZ_GAMEOBJECT

#include <frameworkHaz/Geometry/2D/Vector.hpp>

#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Tools/EnumFlag.hpp>
#include <frameworkHaz/Tools/Time.hpp>

#include <frameworkHaz/Interface/UniqueID.hpp>

#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

ENUM_FLAG_NESTED(BEG_NAMESPACE_HAZ, END_NAMESPACE_HAZ, 
Layers, {
    Default         = 1 << 0,
    Light           = 1 << 1,
    RayCast         = 1 << 2,
    UI              = 1 << 3,
    Ground          = 1 << 4,
    OnGround        = 1 << 5,
    AboveGround     = 1 << 6,
    Sky             = 1 << 7,
    Wall            = 1 << 8,
    
    Custom_0        = 1 << 10,
    Custom_1        = 1 << 11,
    Custom_2        = 1 << 12,
    Custom_3        = 1 << 13,
    Custom_4        = 1 << 14,
    Custom_5        = 1 << 15,
    Custom_6        = 1 << 16,
    Custom_7        = 1 << 17,
    Custom_8        = 1 << 18,
    Custom_9        = 1 << 19,

    ForeGround      = 1 << 20,
    FrontGround     = 1 << 21,
    MiddleGround    = 1 << 22,
    BackGround      = 1 << 23,

    All             = ~0
});

BEG_NAMESPACE_HAZ_2D

class Transform;

END_NAMESPACE_HAZ_2D

BEG_NAMESPACE_HAZ

class Component;

class GameObject {
public:
    /* Ctor Dtor ... */
    GameObject(std::string const& name, _2D::Vectorf const& position = _2D::Vectorf::zero(), float rotation = 0, _2D::Vectorf const& scale = _2D::Vectorf::units());
    GameObject(GameObject const& go);
    GameObject& operator=(GameObject go);
    ~GameObject();
    
    static void swap(GameObject& a, GameObject& b);

    /* Components Modifiers */
#define TEMP_COMP template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>

#define TEMP_COMP_AS_ARGS template<typename T, typename As = T, typename ...Args, typename = typename std::enable_if<std::is_base_of<Component, As>::value>::type, typename = typename std::enable_if<std::is_base_of<As, T>::value>::type>
#define TEMP_COMP_AS template<typename T, typename As = T, typename = typename std::enable_if<std::is_base_of<Component, As>::value>::type, typename = typename std::enable_if<std::is_base_of<As, T>::value>::type>
    TEMP_COMP_AS_ARGS T* addComponent(Args... args);
    TEMP_COMP_AS T* addComponent();

    TEMP_COMP void removeComponent();
#undef TEMP_COMP_AS
#undef TEMP_COMP_AS_ARGS

    /* Components Query */
    TEMP_COMP T* getComponent();
    TEMP_COMP const T* getComponent() const;
              std::vector<Component*> getComponents();
              std::vector<const Component*> getComponents() const;

    TEMP_COMP T* getComponentInChilds();
    TEMP_COMP const T* getComponentInChilds() const;
    TEMP_COMP std::vector<T*> getComponentsInChilds();
    TEMP_COMP std::vector<const T*> getComponentsInChilds() const;

    TEMP_COMP T* getComponentInParents();
    TEMP_COMP const T* getComponentInParents() const;
    TEMP_COMP std::vector<T*> getComponentsInParents();
    TEMP_COMP std::vector<const T*> getComponentsInParents() const;
#undef TEMP_COMP

    /* Parent / Childs */
    void parent(GameObject* go);
    GameObject* parent();
    const GameObject* parent() const;
    void addChild(GameObject* go);
    std::vector<GameObject*> childs();
    std::vector<GameObject const*> childs() const;

    /* Transform */
    _2D::Transform* transform();
    _2D::Transform const* transform() const;
    
    /* Name */
    std::string to_string() const;
    void pretty_console() const;
    void name(std::string const& n);
    std::string name() const;
    bool compareName(std::string const& n);

    /* Tag */
    std::string tag() const;
    void tag(std::string const& t);
    bool compareTag(std::string const& t);

    /* Active */
    bool isActive() const;
    void setActive(bool b);

    /* Layers */
    bool isOnAnyLayer(Layers l) const;
    bool isOnAllLayers(Layers l) const;
    void AddLayer(Layers l);
    void setLayers(Layers l);
    void removeLayers(Layers l);
    Layers layers() const;

private:
    /* Members */
    std::map<std::size_t, Component*> components;

    GameObject* _parent = nullptr;
    std::vector<GameObject*> _childs = {};

    _2D::Transform* tf;

    std::string _name;
    std::string _tag = "";

    bool is_active = true;
    Layers _layers = Layers::Default | Layers::RayCast;
};

class Environement;

class Component : public UniqueID {
public:
    /* Ctor Dtor */
    Component(GameObject* go);
    virtual ~Component();    
    virtual Component* clone(GameObject* go) const = 0;    

    /* Stringify */
    static std::map<long, std::string> component_to_string;
    
    virtual std::string to_string() const;
    virtual std::vector<std::string> pretty_strings () const;
    
    /* Getter GameObject / Transform */
    GameObject* gameobject ();
    const GameObject* gameobject () const;
    _2D::Transform* transform ();
    const _2D::Transform* transform () const;

    /* Tag / Name */
    std::string name() const;
    void name(std::string const& n);
    std::string tag() const;
    void tag(std::string const& t);

#define TEMP_COMP template<typename C, typename = typename std::enable_if<std::is_base_of<Component, C>::value>::type>
#define TEMP_COMP_AS_ARGS template<typename T, typename As = T, typename ...Args, typename = typename std::enable_if<std::is_base_of<Component, As>::value>::type, typename = typename std::enable_if<std::is_base_of<As, T>::value>::type>
#define TEMP_COMP_AS template<typename T, typename As = T, typename = typename std::enable_if<std::is_base_of<Component, As>::value>::type, typename = typename std::enable_if<std::is_base_of<As, T>::value>::type>
    
    /* Component Modifier */
    TEMP_COMP_AS_ARGS T* addComponent(Args... args);
    TEMP_COMP_AS T* addComponent();

    TEMP_COMP void removeComponent();
#undef TEMP_COMP_AS
#undef TEMP_COMP_AS_ARGS
    
    /* Components Query */
    TEMP_COMP C* getComponent();
    TEMP_COMP const C* getComponent() const;
              std::vector<Component*> getComponents();
              std::vector<const Component*> getComponents() const;

    TEMP_COMP C* getComponentInChilds();
    TEMP_COMP const C* getComponentInChilds() const;
    TEMP_COMP std::vector<C*> getComponentsInChilds();
    TEMP_COMP std::vector<const C*> getComponentsInChilds() const;

    TEMP_COMP C* getComponentInParents();
    TEMP_COMP const C* getComponentInParents() const;
    TEMP_COMP std::vector<C*> getComponentsInParents();
    TEMP_COMP std::vector<const C*> getComponentsInParents() const;
#undef TEMP_COMP
    
    /* Update */
    virtual void update(Time const& t, Environement* e);

    /* Event when disble or enable */
    virtual void onEnable();
    virtual void onDisable();

    /* std::cout */
    friend std::ostream& operator << (std::ostream& os, Component const& c);

    /* Instance ID */
    bool operator == (Component const& c) const;
    bool operator != (Component const& c) const;
    std::uintptr_t getInstanceID () const;

private:
    GameObject* go = nullptr;
    _2D::Transform* tf = nullptr;
};

#define TEMP_COMP template<typename T, typename>
#define TEMP_COMP_AS template<typename T, typename As, typename , typename>
#define TEMP_COMP_AS_ARGS template<typename T, typename As, typename ...Args, typename , typename>

TEMP_COMP_AS_ARGS 
T* Component::addComponent(Args... args) {
    return go->addComponent<T, As, Args...>(args...);
}

TEMP_COMP_AS 
T* Component::addComponent() {
    return go->addComponent<T, As>();
}

TEMP_COMP 
void Component::removeComponent() {
    return go->removeComponent<T>();
}

TEMP_COMP
T* Component::getComponent() {
    return go->getComponent<T>();
}

TEMP_COMP
const T* Component::getComponent() const {
    return go->getComponent<T>();
}

TEMP_COMP 
T* Component::getComponentInChilds() {
    return go->getComponentInChilds<T>();
}

TEMP_COMP 
const T* Component::getComponentInChilds() const {
    return go->getComponentInChilds<T>();
}

TEMP_COMP 
std::vector<T*> Component::getComponentsInChilds() {
    return go->getComponentsInChilds<T>();
}

TEMP_COMP 
std::vector<const T*> Component::getComponentsInChilds() const {
    return go->getComponentsInChilds<T>();
}

TEMP_COMP 
T* Component::getComponentInParents() {
    return go->getComponentInParents<T>();
}

TEMP_COMP 
const T* Component::getComponentInParents() const {
    return go->getComponentInParents<T>();
}

TEMP_COMP 
std::vector<T*> Component::getComponentsInParents() {
    return go->getComponentsInParents<T>();
}

TEMP_COMP 
std::vector<const T*> Component::getComponentsInParents() const {
    return go->getComponentsInParents<T>();
}

#undef TEMP_COMP

#define TEMP_COMP template<typename T, typename>
#define TEMP_COMP_AS template<typename T, typename As, typename , typename>
#define TEMP_COMP_AS_ARGS template<typename T, typename As, typename ...Args, typename , typename>

/* Component */
TEMP_COMP_AS_ARGS T* GameObject::addComponent(Args... args) {
    std::size_t key = typeid(As).hash_code();
    if(components.find(key) != components.end())
        return dynamic_cast<T*>(components[key]);

    Component::component_to_string[key] = haz::demangleTypeIdName(typeid(As).name());

    auto t = new T(this, args...);
    components[key] = t;
    t->onEnable();
    return t;
}

TEMP_COMP_AS T* GameObject::addComponent() {
    std::size_t key = typeid(As).hash_code();
    if(components.find(key) != components.end())
        return dynamic_cast<T*>(components[key]);

    Component::component_to_string[key] = haz::demangleTypeIdName(typeid(As).name());
        
    auto t = new T(this);
    components[key] = t;
    t->onEnable();
    return t;
}

TEMP_COMP void GameObject::removeComponent() {
    std::size_t key = typeid(T).hash_code();
    if(components.find(key) == components.end())
        return;

    auto* c = components[key];
    c->onDisable();
    delete c;
    components.erase(key);
}

TEMP_COMP T* GameObject::getComponent() {
    std::size_t key = typeid(T).hash_code();
    if (components.find(key) == components.end())
        return nullptr;
    else 
        return dynamic_cast<T*>(components[key]);
}

TEMP_COMP const T* GameObject::getComponent() const {
    std::size_t key = typeid(T).hash_code();
    if (components.find(key) == components.end())
        return nullptr;
    else 
        return dynamic_cast<T*>(components.at(key));
}

TEMP_COMP std::vector<T*> GameObject::getComponentsInChilds() {
    std::vector<T*> v = {};
    T* comp = getComponent<T>();
    if (comp != nullptr) {
        v.push_back(comp);
    }
    
    for (auto* c : _childs) {
        for (auto* cp : c->getComponentsInChilds<T>())
            v.push_back(cp);
    }
    return v;
}

TEMP_COMP std::vector<const T*> GameObject::getComponentsInChilds() const {
    std::vector<const T*> v = {};
    const T* comp = getComponent<T>();
    if (comp != nullptr)
        v.push_back(comp);
    
    for (auto* c : _childs) {
        for (auto* cp : c->getComponentsInChilds<T>())
            v.push_back(cp);
    }
    return v;
}

TEMP_COMP T* GameObject::getComponentInChilds() {
    T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;
    
    for (auto* c : _childs)
        for (auto* cp : c->getComponentsInChilds<T>())
            if (cp != nullptr)
                return cp;
    
    return nullptr;
}

TEMP_COMP const T* GameObject::getComponentInChilds() const {
    const T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;
    
    for (auto* c : _childs)
        for (auto* cp : c->getComponentsInChilds<T>())
            if (cp != nullptr)
                return cp;
    
    return nullptr;
}

TEMP_COMP T* GameObject::getComponentInParents() {
    T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;

    return _parent == nullptr ? nullptr : _parent->getComponentInParents<T>();
}

TEMP_COMP const T* GameObject::getComponentInParents() const {
    const T* comp = getComponent<T>();
    if (comp != nullptr)
        return comp;

    return _parent == nullptr ? nullptr : _parent->getComponentInParents<T>();
}

TEMP_COMP std::vector<T*> GameObject::getComponentsInParents() {
    std::vector<T*> v = {};
    T* comp = getComponent<T>();
    if (comp != nullptr) {
        v.push_back(comp);
    }
    
    if (_parent != nullptr) {
        for (auto* cp : _parent->getComponentsInParents<T>())
            v.push_back(cp);
    }
    return v;
}

TEMP_COMP std::vector<const T*> GameObject::getComponentsInParents() const {
    std::vector<const T*> v = {};
    const T* comp = getComponent<T>();
    if (comp != nullptr)
        v.push_back(comp);
    
    if (_parent != nullptr) {
        for (auto* cp : _parent->getComponentsInParents<T>())
            v.push_back(cp);
    }
    return v;
}

#undef TEMP_COMP
#undef TEMP_COMP_AS
#undef TEMP_COMP_AS_ARGS

END_NAMESPACE_HAZ

#endif