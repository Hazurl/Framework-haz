#include <haz/GameObject/GameObject.hpp>

BEG_NAMESPACE_HAZ

std::map<long, std::string> Component::component_to_string;

Component::Component(GameObject* go) : go(go), tf(go->transform()) {}
Component::~Component() {}

std::string Component::to_string() const {
    return "";
}

std::vector<std::string> Component::pretty_strings () const {
    return {};
}

GameObject* Component::gameobject () {
    return go;
}

const GameObject* Component::gameobject () const {
    return go;
}

const NS_HAZ_2D::Transform* Component::transform () const {
    return tf;
}

NS_HAZ_2D::Transform* Component::transform () {
    return tf;
}

std::string Component::name() const {
    return go->name();
}

void Component::name(std::string const& n) {
    return go->name(n);
}

std::string Component::tag() const {
    return go->tag();
}

void Component::tag(std::string const& t) {
    return go->tag(t);
}

void Component::update() {}
void Component::onEnable() {}
void Component::onDisable() {}

std::ostream& operator << (std::ostream& os, Component const& c) {
    os << c.to_string();
    return os;
}

std::vector<Component*> Component::getComponents() {
    return go->getComponents();
}

std::vector<const Component*> Component::getComponents() const {
    return static_cast<const GameObject*>(go)->getComponents();
}

bool Component::operator == (Component const& c) const {
    return id == c.id;
}

bool Component::operator != (Component const& c) const {
    return !(c == *this);
}

std::uintptr_t Component::getInstanceID () const {
    return id;
}

END_NAMESPACE_HAZ