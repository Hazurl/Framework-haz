#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>

BEG_NAMESPACE_HAZ

GameObject::GameObject(std::string const& name, _2D::Vectorf const& position, float rotation, _2D::Vectorf const& scale) 
    : components({}), tf(addComponent<_2D::Transform>(position, scale, rotation)), name(name) {

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

GameObject* GameObject::getParent() {
    return parent;
}

const GameObject* GameObject::getParent() const {
    return parent;
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

_2D::Transform& GameObject::transform() {
    return *tf;
}

_2D::Transform const& GameObject::transform() const {
    return *tf;
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

void GameObject::pretty_console() const {
    std::vector<std::vector<std::string>> str_comp;

    std::string title = "[" + adress(this) + "] " + name;
    if (tag.size() > 0) title += " @" + tag;

    unsigned int lgth = title.size();

    for (auto& p : components) {
        std::vector<std::string> block { removeNameSpaceOfClassName(Component::component_to_string[p.first]) };
        auto b = p.second->pretty_strings();
        
        block.insert(block.end(), b.begin(), b.end());

        for (auto& s : block) {
            lgth = max<unsigned int>(lgth, s.size());
        }
        str_comp.push_back(block);
        if (p.second == tf) {
            std::swap(str_comp[0], str_comp.back());
        }
    }
    
    std::cout << "╔ " << title << " ";
    for (unsigned int i = 0; i < (lgth - title.size()) + 2; i++)
        std::cout << "═";
    std::cout << "╗" << std::endl;

    for (auto& block : str_comp) {
        std::cout << "║┌ " << block[0] << " ";
        for (unsigned int i = 0; i < (lgth - block[0].size()); i++)
            std::cout << "─";
        std::cout << "┐║" << std::endl;
    
        for (unsigned int i = 1; i < block.size(); i++) {
            std::cout << "║│ " << block[i] << std::string(lgth - block[i].size(), ' ') << " │║" << std::endl;
        }
    
        std::cout << "║└";
        for (unsigned int i = 0; i < lgth + 2; i++)
            std::cout << "─";
        std::cout << "┘║" << std::endl;
    }

    std::cout << "╚";
    for (unsigned int i = 0; i < lgth + 4; i++)
        std::cout << "═";
    std::cout << "╝" << std::endl;
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