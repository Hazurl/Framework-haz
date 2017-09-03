#include <frameworkHaz/GameObject/GameObject.hpp>

#include <frameworkHaz/GameObject/2D/Physic.hpp>

#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>
#include <frameworkHaz/GameObject/Component/2D/BoxCollider.hpp>
#include <frameworkHaz/GameObject/Component/2D/CircleCollider.hpp>

#include <frameworkHaz/Tools/Macro.hpp>
#include <iostream>

#include <frameworkHaz/Interface/Factory.hpp>
#include <frameworkHaz/Interface/RessourceLoader.hpp>

//#include <frameworkHaz/2DGOInclude.hpp>


int main (int , char ** ) {
    USING_NS_HAZ
    USING_NS_HAZ_2D
    USING_NS_HAZ_COLLISION

    typedef Factory<GameObject, std::string, GameObject::CopyAllocator> go_fact;

    auto* _A = new GameObject("A");
    _A->addComponent<BoxCollider>(5, 5, 100, 100);

    go_fact::registerObject("A", _A);

    auto* g = go_fact::createObject("A");
    WRITE(g->getComponents().size());

    WRITE(g->to_string() << " -> " << g->getComponent<BoxCollider>()->position());

    Time time;

    (new GameObject("base", Vectorf{1, 1}))->addComponent<BoxCollider>(0, 0, 10, 8)->tag("FloorTag");
    (new GameObject("a"))->addComponent<CircleCollider>(1, 0, 5);
    (new GameObject("b"))->addComponent<BoxCollider>(-1, -1, 0.9, 0.9);

    std::array<GameObject*, 1> gos;
    int count = Physic::raycast(Vectorf{0, 0}, gos);

    if (count > 0) {
        for (GameObject* go : gos) {
            if (--count >= 0) {
                WRITE("Hit : " << go->to_string());
                go->pretty_console();
            } else
                break;
        }
    }

    for (GameObject* go : Physic::raycast_all(Vectorf{0, 0}))
        WRITE("Hit : " << go->to_string());

    typedef RessourceLoader<std::string> RL;

    std::string* s = RL::loadGlobal("ok");
    std::string* ss = RL::getGlobal("ok");

    std::cout << s << ", " << ss << std::endl;

    typedef RessourceLoader<std::string, std::string, int> RR;
    
    std::string* q = RR::loadGlobal("ok", 0);
    std::string* qq = RR::getGlobal(0);

    std::cout << q << ", " << qq << std::endl;

    (new GameObject("GameObject's name", Vectorf{10, 10}, 45, Vectorf{2, 2}))
        ->addComponent<BoxCollider>(Vectorf{-5, -5}, Vectorf{10, 10})
        ->addComponent<EdgeCollider>(std::vector<Vectorf>{{100, 100}, {101, 100}, {101, 101}, {100, 101}}, 10);

    GameObject* _fisrt_hit = Physic::raycast_first(Vectorf{15, 15});
    if (_fisrt_hit == nullptr) {
        std::cout << "No Gameobject hit !" << std::endl;
    } else {
        _fisrt_hit->pretty_console();
    }

    GameObject* fisrt_hit = Physic::raycast_first(Vectorf{110, 105});
    if (fisrt_hit == nullptr) {
        std::cout << "No Gameobject hit !" << std::endl;
    } else {
        fisrt_hit->pretty_console();
    }

    return 0;
}