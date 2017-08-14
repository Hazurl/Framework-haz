#include <frameworkHaz/GameObject/GameObject.hpp>

#include <frameworkHaz/GameObject/Environement.hpp>

#include <frameworkHaz/GameObject/2D/Physic.hpp>

#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>
#include <frameworkHaz/GameObject/Component/2D/BoxCollider.hpp>
#include <frameworkHaz/GameObject/Component/2D/CircleCollider.hpp>

#include <frameworkHaz/Tools/Macro.hpp>
#include <iostream>

#include <frameworkHaz/Interface/Factory.hpp>
#include <frameworkHaz/Interface/RessourceLoader.hpp>

int main (int , char ** ) {
    USING_NS_HAZ
    USING_NS_HAZ_2D
    USING_NS_HAZ_COLLISION

    typedef Factory<GameObject> go_fact;

    auto* _A = new GameObject("A");
    _A->addComponent<BoxCollider>(5, 5, 100, 100);

    go_fact::registerObject("A", _A);

    auto* g = go_fact::createObject("A");
    WRITE(g->getComponents().size());

    WRITE(g->to_string() << " -> " << g->getComponent<BoxCollider>()->position());

    delete g;

    Time time;

    Environement e;
    e.addGameObject(new GameObject("base"))->addComponent<BoxCollider>(0, 0, 10, 8);
    e.addGameObject(new GameObject("a"))->addComponent<CircleCollider>(1, 0, 5);
    e.addGameObject(new GameObject("b"))->addComponent<BoxCollider>(-1, -1, 0.9, 0.9);

    std::array<GameObject*, 1> gos;
    int count = Physic::raycast(&e, Vectorf{0, 0}, gos);

    if (count > 0) {
        for (GameObject* go : gos) {
            if (--count >= 0)
                WRITE("Hit : " << go->to_string());
            else
                break;
        }
    }

    for (GameObject* go : Physic::raycast_all(&e, Vectorf{0, 0}))
        WRITE("Hit : " << go->to_string());

    typedef RessourceLoader<std::string> RL;

    std::string* s = RL::loadGlobal("ok");
    std::string* ss = RL::getGlobal("ok");

    std::cout << s << ", " << ss << std::endl;

    typedef RessourceLoader<std::string, std::string, int> RR;
    
    std::string* q = RR::loadGlobal("ok", 0);
    std::string* qq = RR::getGlobal(0);

    std::cout << q << ", " << qq << std::endl;
    
    return 0;
}