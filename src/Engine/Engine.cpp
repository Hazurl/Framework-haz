#include <frameworkHaz/Engine/Engine.hpp>

#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/Tools/Time.hpp>

BEG_NAMESPACE_HAZ

Engine::~Engine() {
    Engine::reset();
}

Time const& Engine::time () {
    return *get()._time;
}

void Engine::reset() {
    GameObject::destroyAll();
    if (get()._time != nullptr) {
        delete get()._time;
        get()._time = nullptr;
    }
}

void Engine::start() {
    get()._time = new Time();
}

void Engine::update() {
    for(auto* go : get().roots) {
        go->update();
    }
}

END_NAMESPACE_HAZ
