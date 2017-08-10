#include <GameObject/Component/Component.hpp>

BEG_NAMESPACE_HAZ

Component::Component(GameObject* go) : go(go) {

}

GameObject* Component::getGO () {
    return go;
}

const GameObject* Component::getGO () const {
    return go;
}

void Component::update(Time const&, Environement* ) {}

END_NAMESPACE_HAZ