#include <GameObject/Component.hpp>

BEG_NAMESPACE_HAZ

GameObject* Component::getGO () {
    return go;
}

const GameObject* Component::getGO () const {
    return go;
}

void Component::update(Time const&) {}

END_NAMESPACE_HAZ