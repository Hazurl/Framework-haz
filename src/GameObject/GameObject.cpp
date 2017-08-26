#include <frameworkHaz/GameObject/GameObject.hpp>

BEG_NAMESPACE_HAZ

GameObject::GameObject(std::string const& name) : components({}), name(name) {
    
}

GameObject::~GameObject() {
    for (auto& p : components)
        delete p.second;

    components.clear();
}

GameObject::GameObject(GameObject const& o) : parent(o.parent), name(o.name), tag(o.tag), is_active(o.is_active), layers(o.layers) {
    // Components
    for (auto& p : o.components) 
        (components[p.first] = p.second->clone(this))->onEnable();

    // Childs
    for (auto* child : o.childs) 
        childs.push_back(new GameObject(*child));
}

GameObject& GameObject::operator=(GameObject go) {
    swap(*this, go);
    return *this;
}

void GameObject::swap(GameObject& a, GameObject& b) {
    haz::swap(a.components, b.components);
}

std::vector<Component*> GameObject::getComponents() {
    std::vector<Component*> v;
    for (auto& p : components)
        v.push_back(p.second);
    return v;
}

std::vector<const Component*> GameObject::getComponents() const {
    std::vector<const Component*> v;
    for (auto& p : components)
        v.push_back(p.second);
    return v;
}

void GameObject::setParent(GameObject* go) {
    if (parent != nullptr) {
        auto it = std::find(parent->childs.begin(), parent->childs.end(), this);
        if (it != parent->childs.end())
            parent->childs.erase(it);
    }

    if (go != nullptr)
        go->childs.push_back(this);
    parent = go;
}


void GameObject::addChild(GameObject* go) {
    if (go != nullptr)
        go->setParent(this);
}

std::vector<GameObject const*> GameObject::getChilds() const {
    std::vector<GameObject const*> cs = {};
    for (auto* c : childs)
        cs.push_back(c);

    return cs;
}

std::vector<GameObject*> GameObject::getChilds() {
    return childs;
}

std::string GameObject::to_string() const {
    std::string s = name;
    s += " : ";
    bool is_first = true;
    for (auto& p : components) {
        if (is_first) is_first = false;
        else s += ", ";
        s += "[" + adress(p.second) + "] " + Component::component_to_string[p.first] + p.second->to_string();
    }

    return s;
}

void GameObject::setName(std::string const& n) {
    name = n;
}

bool GameObject::compareName(std::string const& n) {
    return name == n;
}

std::string GameObject::getTag() const {
    return tag;
}

void GameObject::setTag(std::string const& t) {
    tag = t;
}

bool GameObject::compareTag(std::string const& t) {
    return tag == t;
}

bool GameObject::isActive() const {
    return is_active;
}

void GameObject::setActive(bool b) {
    if (is_active != b) {
        if (b) {
            for (auto& p : components)
                p.second->onEnable();
        } else {
            for (auto& p : components)
                p.second->onDisable();
        }
        is_active = b;
        
        for(auto* c : childs) {
            c->setActive(b);
        }
    }
}

bool GameObject::isOnAnyLayer(Layers l) const {
    return layers & l;
}

bool GameObject::isOnAllLayers(Layers l) const {
    return (l & layers) == l;
}

void GameObject::AddLayer(Layers l) {
    layers |= l;
}

void GameObject::setLayers(Layers l) {
    layers = l;
}

void GameObject::removeLayers(Layers l) {
    layers &= ~l;
}

Layers GameObject::getLayers() const {
    return layers;
}

END_NAMESPACE_HAZ