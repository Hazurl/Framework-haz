#include <GameObject/GameObject.hpp>

#include <GameObject/Environement.hpp>

#include <GameObject/2D/Physic.hpp>

#include <GameObject/Component/2D/Transform.hpp>
#include <GameObject/Component/2D/BoxCollider.hpp>
#include <GameObject/Component/2D/CircleCollider.hpp>

#include <Tools/Macro.hpp>
#include <iostream>

#include <Interface/Factory.hpp>

int main (int , char ** ) {
    USING_NS_HAZ
    USING_NS_HAZ_HIDDEN
    USING_NS_HAZ_2D
    USING_NS_HAZ_COLLISION

    typedef Factory<GameObject> go_fact;

    auto* _A = new GameObject("A");
    _A->addComponent<BoxCollider>(5, 5, 100, 100);

    go_fact::registerObject("A", _A);

    auto* g = go_fact::createObject("A");
    WRITE(g->getComponents().size());

    WRITE(g->to_string() << " -> " << g->getComponent<BoxCollider>()->position());

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

    return 0;
}