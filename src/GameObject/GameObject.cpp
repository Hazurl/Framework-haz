#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>

BEG_NAMESPACE_HAZ

GameObject::GameObject(std::string const& name, _2D::Vectorf const& position, float rotation, _2D::Vectorf const& scale) 
    : components({}), tf(new _2D::Transform(this, position, scale, rotation)), _name(name) {

}

GameObject::~GameObject() {
    for (auto& p : components)
        delete p.second;

    components.clear();

    for (auto* c : _childs)
        delete c;

    _childs.clear();

    delete tf;
}

GameObject::GameObject(GameObject const& o) : _parent(o._parent), tf(dynamic_cast<_2D::Transform*>(o.tf->clone(this))), _name(o._name), _tag(o._tag), is_active(o.is_active), _layers(o._layers) {
    // Components
    for (auto& p : o.components) 
        (components[p.first] = p.second->clone(this))->onEnable();

    // Childs
    for (auto* child : o._childs) 
        _childs.push_back(new GameObject(*child));
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
    for (auto& p : components) {
        v.push_back(p.second);
    }
    return v;
}

std::vector<const Component*> GameObject::getComponents() const {
    std::vector<const Component*> v;
    for (auto& p : components) {
        v.push_back(p.second);
    }
    return v;
}

void GameObject::parent(GameObject* go) {
    if (_parent != nullptr) {
        auto it = std::find(_parent->_childs.begin(), _parent->_childs.end(), this);
        if (it != _parent->childs().end())
            _parent->_childs.erase(it);
    }

    if (go != nullptr)
        go->_childs.push_back(this);
    _parent = go;
}

GameObject* GameObject::parent() {
    return _parent;
}

const GameObject* GameObject::parent() const {
    return _parent;
}

void GameObject::addChild(GameObject* go) {
    if (go != nullptr)
        go->parent(this);
}

std::vector<GameObject const*> GameObject::childs() const {
    return { _childs.begin(), _childs.end() };
}

std::vector<GameObject*> GameObject::childs() {
    return _childs;
}

_2D::Transform* GameObject::transform() {
    return tf;
}

const _2D::Transform* GameObject::transform() const {
    return tf;
}

std::string GameObject::to_string() const {
    std::string s = _name;
    s += " : ";
    bool is_first = true;
    for (auto& p : components) {
        if (is_first) is_first = false;
        else s += ", ";
        s += "[" + adress(p.second) + "] " + removeNameSpaceOfClassName(Component::component_to_string[p.first]);
    }

    return s;
}

void GameObject::pretty_console() const {
    std::vector<std::vector<std::string>> str_comp;

    std::string title = "[" + adress(this) + "] " + _name;
    if (_tag.size() > 0) title += " @" + _tag;

    unsigned int lgth = title.size();
    {
        std::vector<std::string> block { removeNameSpaceOfClassName(TYPE_NAME(*tf)) };
        auto b = tf->pretty_strings();
        
        block.insert(block.end(), b.begin(), b.end());

        for (auto& s : block) {
            lgth = max<unsigned int>(lgth, s.size());
        }
        str_comp.push_back(block);
    }

    for (auto& p : components) {
        std::vector<std::string> block { removeNameSpaceOfClassName(Component::component_to_string[p.first]) };
        auto b = p.second->pretty_strings();
        
        block.insert(block.end(), b.begin(), b.end());

        for (auto& s : block) {
            lgth = max<unsigned int>(lgth, s.size());
        }
        str_comp.push_back(block);
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

void GameObject::name(std::string const& n) {
    _name = n;
}

std::string GameObject::name() const {
    return _name;
}

bool GameObject::compareName(std::string const& n) {
    return _name == n;
}

std::string GameObject::tag() const {
    return _tag;
}

void GameObject::tag(std::string const& t) {
    _tag = t;
}

bool GameObject::compareTag(std::string const& t) {
    return _tag == t;
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
        
        for(auto* c : _childs) {
            c->setActive(b);
        }
    }
}

bool GameObject::isOnAnyLayer(Layers l) const {
    return _layers & l;
}

bool GameObject::isOnAllLayers(Layers l) const {
    return (l & _layers) == l;
}

void GameObject::AddLayer(Layers l) {
    _layers |= l;
}

void GameObject::setLayers(Layers l) {
    _layers = l;
}

void GameObject::removeLayers(Layers l) {
    _layers &= ~l;
}

Layers GameObject::layers() const {
    return _layers;
}

END_NAMESPACE_HAZ