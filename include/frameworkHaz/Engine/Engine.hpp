#ifndef __HAZ_ENGINE
#define __HAZ_ENGINE

#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Interface/Singleton.hpp>
#include <frameworkHaz/Tools/Time.hpp>

#include <unordered_set>

BEG_NAMESPACE_HAZ_2D

class Physic;

END_NAMESPACE_HAZ_2D

BEG_NAMESPACE_HAZ

class GameObject;
class Component;

class Engine : private Singleton<Engine> {
    friend Singleton<Engine>;
    friend GameObject;
    friend Component;
    friend NS_HAZ_2D::Physic;

public:

    static Time const& time ();

    static void reset();
    static void start();
    static void update();
    
private:

    std::unordered_set<GameObject*> gameobjects;
    std::unordered_set<GameObject*> roots;

    Time* _time;

    ~Engine();

};

END_NAMESPACE_HAZ

#endif
