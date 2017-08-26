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

#include <frameworkHaz/2DGOInclude.hpp>


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
    e.addGameObject(new GameObject("base", {1, 1}))->addComponent<BoxCollider>(0, 0, 10, 8);
    e.find_GO_of_name("base")->setTag("FloorTag");
    e.addGameObject(new GameObject("a"))->addComponent<CircleCollider>(1, 0, 5);
    e.addGameObject(new GameObject("b"))->addComponent<BoxCollider>(-1, -1, 0.9, 0.9);

    std::array<GameObject*, 1> gos;
    int count = Physic::raycast(&e, Vectorf{0, 0}, gos);

    if (count > 0) {
        for (GameObject* go : gos) {
            if (--count >= 0) {
                WRITE("Hit : " << go->to_string());
                go->pretty_console();
            } else
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

    Environement ee;

    GameObject* go = new GameObject("GameObject's name", {10, 10}, 45, {2, 2});
    go->addComponent<BoxCollider>(Vectorf{-5, -5}, Vectorf{10, 10});
    //go->addComponent<EdgeCollider>(std::vector<Vectorf>{{0, 0}, {1, 0}, {1, 1}, {0, 1}}, 1);

    ee.addGameObject(go);

    GameObject* fisrt_hit = Physic::raycast_first(&ee, Vectorf{15, 15});
    if (fisrt_hit == nullptr) {
        std::cout << "No Gameobject hit !" << std::endl;
    } else {
        fisrt_hit->pretty_console();
    }

    return 0;
}