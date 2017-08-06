TEMPLATE_T
std::vector<T*> Environement::getComponents() {
    std::vector<T*> v = {};
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            v.push_back(c);

    return v;
}

TEMPLATE_T
std::vector<const T*> Environement::getComponents() const {
    std::vector<const T*> v = {};
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            v.push_back(c);

    return v;
}

TEMPLATE_T
T* Environement::getComponent() {
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            return c;

    return nullptr;
}

TEMPLATE_T
const T* Environement::getComponent() const {
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            return c;
    
    return nullptr;
}
