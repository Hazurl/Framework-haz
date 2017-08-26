#include <frameworkHaz/GameObject/Component/Component.hpp>

BEG_NAMESPACE_HAZ

std::map<long, std::string> Component::component_to_string = {};

Component::Component(GameObject* go) : go(go) {

}

Component::~Component() {

}

std::string Component::to_string() const {
    return "";
}

GameObject* Component::getGO () {
    return go;
}

const GameObject* Component::getGO () const {
    return go;
}

void Component::update(Time const&, Environement* ) {

}

void Component::onEnable() {

}

void Component::onDisable() {
    
}

END_NAMESPACE_HAZ