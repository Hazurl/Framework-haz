#include <GameObject/GameObject.hpp>

BEG_NAMESPACE_HAZ

GameObject::GameObject(std::string const& name) : components({}), name(name) {}

GameObject::~GameObject() {
    for (auto& p : components) {
        std::cout << "Delete : " << TYPE_NAME(*p.second) << std::endl;
        delete p.second;
    }
    components.clear();
}

GameObject::GameObject(GameObject const& go) {
    *this = go;
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

std::string GameObject::to_string() const {
    return name;
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
    is_active = b;
}

bool GameObject::isOnLayer(Layer l) const {
    return layers & l;
}

void GameObject::setOnLayer(Layer l) {
    layers |= l;
}

void GameObject::removefromLayer(Layer l) {
    layers &= ~l;
}

Layer GameObject::getLayers() const {
    return layers;
}

END_NAMESPACE_HAZ