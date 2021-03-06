#include <haz/Engine/Engine.hpp>

#include <haz/GameObject/GameObject.hpp>
#include <haz/Tools/Time.hpp>

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
    get()._time->update();
    for(auto* go : get().gameobjects) {
        go->update();
    }
}

END_NAMESPACE_HAZ
