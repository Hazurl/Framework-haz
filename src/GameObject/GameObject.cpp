#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>

BEG_NAMESPACE_HAZ

GameObject::GameObject(std::string const& name, _2D::Vectorf const& position, float rotation, _2D::Vectorf const& scale) 
    : components({}), tf(new _2D::Transform(this, position, scale, rotation)), _name(name) {
    Engine::get().gameobjects.insert(this);
    Engine::get().roots.insert(this);
}

GameObject::~GameObject() {
    for (auto& p : components)
        delete p.second;

    components.clear();

    for (auto* c : _childs)
        c->destroy();

    _childs.clear();

    delete tf;
}

void GameObject::destroy() {
    Engine::get().gameobjects.erase(this);
    if (_parent == nullptr)
        Engine::get().roots.erase(this);

    delete this;
}

void GameObject::destroyAll() {
    for(auto* go : Engine::get().roots) {
        delete go;
    }
    Engine::get().gameobjects.clear();
    Engine::get().roots.clear();
}

void GameObject::detach() {
    Engine::get().gameobjects.erase(this);
    if (_parent == nullptr)
        Engine::get().roots.erase(this);

    for (auto* c : _childs)
        c->detach();
}

GameObject::GameObject(GameObject const& o) 
    : _parent(o._parent), tf(dynamic_cast<_2D::Transform*>(o.tf->clone(this))), _name(o._name), _tag(o._tag), is_active(o.is_active), _layers(o._layers) {
    // Components
    for (auto& p : o.components) 
        (components[p.first] = p.second->clone(this))->onEnable();

    // Childs
    for (auto* child : o._childs) 
        _childs.push_back(new GameObject(*child));

    Engine::get().gameobjects.insert(this);
    Engine::get().roots.insert(this);
}

GameObject::GameObject(GameObject const& go, NS_HAZ_2D::Vectorf const& position, float rotation) : GameObject(go) {
    tf->position(position);
    tf->rotation(rotation);
}

GameObject::GameObject(GameObject const& go, GameObject& parent, NS_HAZ_2D::Vectorf const& position, float rotation) : GameObject(go) {
    tf->position(position);
    tf->rotation(rotation);
    this->parent(&parent);
    Engine::get().roots.erase(Engine::get().gameobjects.find(this));
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

GameObject* GameObject::findOfName(std::string const& name) {
    for (auto* go : Engine::get().gameobjects)
        if (go->compareName(name))
            return go;

    return nullptr;
}

GameObject* GameObject::findOfTag(std::string const& tag) {
    for (auto* go : Engine::get().gameobjects)
        if (go->compareTag(tag))
            return go;

    return nullptr;
}

std::vector<GameObject*> GameObject::findAllOfName(std::string const& name) {
    std::vector<GameObject*> v = {};
    for (auto* go : Engine::get().gameobjects)
        if (go->compareName(name))
            v.push_back(go);

    return v;
}

std::vector<GameObject*> GameObject::findAllOfTag(std::string const& tag) {
    std::vector<GameObject*> v = {};
    for (auto* go : Engine::get().gameobjects)
        if (go->compareTag(tag))
            v.push_back(go);

    return v;
}

std::vector<Component*> GameObject::getAllComponents() {
    std::vector<Component*> v = {};
    for (auto* go : Engine::get().gameobjects)
        for (auto* c : go->getComponents())
            v.push_back(c);

    return v;
}

std::vector<GameObject*> GameObject::getAll() {
    return { Engine::get().gameobjects.begin(), Engine::get().gameobjects.end() };
}

void GameObject::update() {
    for(auto& p : components) {
        p.second->update();
    }
}

void GameObject::parent(GameObject* go) {
    if (go == _parent) {
        return;
    }

    if (_parent != nullptr) {
        auto it = std::find(_parent->_childs.begin(), _parent->_childs.end(), this);
        _parent->_childs.erase(it);

        if (go == nullptr) {
            Engine::get().roots.insert(this);
            return;
        }
    }

    if (go != nullptr) {
        if (_parent == nullptr) {
            Engine::get().roots.erase(this);
        }

        go->_childs.push_back(this);
    }
    
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