#include <frameworkHaz/GameObject/Environement.hpp>

BEG_NAMESPACE_HAZ

/*
 *          Ctor Dtor
 */

Environement::Environement() {}
Environement::~Environement() {
	for (auto* go : gos)
        delete go;
    gos.clear();
}

/*
 *          Component Query : By Name
 */

GameObject* Environement::find_GO_of_name(std::string const& name) {
    for (auto* go : gos)
        if (go->compareName(name))
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
const GameObject* Environement::find_GO_of_name(std::string const& name) const {
    for (auto* go : gos)
        if (go->compareName(name))
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

/*
 *          Component Query : By Tag
 */

GameObject* Environement::find_GO_of_tag(std::string const& tag) {
    for (auto* go : gos)
        if (go->compareTag(tag))
            return go;
    
    return nullptr;
}
std::vector<GameObject*> Environement::find_GOs_of_tag(std::string const& tag) {
    std::vector<GameObject*> v = {};
    for (auto* go : gos)
        if (go->compareTag(tag))
            v.push_back(go);

    return v;
}
const GameObject* Environement::find_GO_of_tag(std::string const& tag) const {
    for (auto* go : gos)
        if (go->compareTag(tag))
            return go;
    
    return nullptr;
}
std::vector<const GameObject*> Environement::find_GOs_of_tag(std::string const& tag) const {
    std::vector<const GameObject*> v = {};
    for (auto* go : gos)
        if (go->compareTag(tag))
            v.push_back(go);

    return v;
}

/*
 *          Component Query : All
 */

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

/*
 *          Debug
 */

void Environement::print_to_tree() {
    for (unsigned int i = 0; i < gos.size(); ++i) {
        print_to_tree_helper(gos[i], "", i == (gos.size() - 1));
    }
}
void Environement::print_to_tree_helper(GameObject* cur, std::string indent, bool is_last) {
    auto text = indent;
    if (is_last) {
        text += "└───";
        indent += "    ";
    } else {
        text += "├───";
        indent += "│  ";
    }

    std::cout << text << " [" << cur << "] " << cur->to_string() << std::endl;

    auto childs = cur->childs();
    for (unsigned int i = 0; i < childs.size(); ++i) {
        print_to_tree_helper(childs[i], indent, i == (childs.size() - 1));
    }
}
END_NAMESPACE_HAZ