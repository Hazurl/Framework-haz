#include <GameObject/Environement.hpp>

BEG_NAMESPACE_HAZ

Environement::Environement() {
	
}

Environement::~Environement() {
	for (auto* go : gos)
        delete go;
    gos.clear();
}

GameObject* Environement::addGameObject(GameObject* go) {
    if (go != nullptr)
        gos.push_back(go);
    return go;
}


std::vector<Component*> Environement::getAllComponents() {
    std::vector<Component*> v = {};
    for (auto* go : gos)
        for (auto* c : go->getComponents())
            v.push_back(c);

    return v;
}

std::vector<const Component*> Environement::getAllComponents() const {
    std::vector<const Component*> v = {};
    for (auto* go : gos)
        for (auto* c : go->getComponents())
            v.push_back(c);

    return v;
}

GameObject* Environement::find_GO_of_name(std::string const& name) {
    for (auto* go : gos)
        if (go->compareName(name))
            return go;
    
    return nullptr;
}

GameObject* Environement::find_GO_of_tag(std::string const& tag) {
    for (auto* go : gos)
        if (go->compareTag(tag))
            return go;
    
    return nullptr;
}

std::vector<GameObject*> Environement::find_GOs_of_name(std::string const& name) {
    std::vector<GameObject*> v = {};
    for (auto* go : gos)
        if (go->compareName(name))
            v.push_back(go);

    return v;
}

std::vector<GameObject*> Environement::find_GOs_of_tag(std::string const& tag) {
    std::vector<GameObject*> v = {};
    for (auto* go : gos)
        if (go->compareTag(tag))
            v.push_back(go);

    return v;
}
const GameObject* Environement::find_GO_of_name(std::string const& name) const {
    for (auto* go : gos)
        if (go->compareName(name))
            return go;
    
    return nullptr;
}

const GameObject* Environement::find_GO_of_tag(std::string const& tag) const {
    for (auto* go : gos)
        if (go->compareTag(tag))
            return go;
    
    return nullptr;
}

std::vector<const GameObject*> Environement::find_GOs_of_name(std::string const& name) const {
    std::vector<const GameObject*> v = {};
    for (auto* go : gos)
        if (go->compareName(name))
            v.push_back(go);

    return v;
}

std::vector<const GameObject*> Environement::find_GOs_of_tag(std::string const& tag) const {
    std::vector<const GameObject*> v = {};
    for (auto* go : gos)
        if (go->compareTag(tag))
            v.push_back(go);

    return v;
}

END_NAMESPACE_HAZ