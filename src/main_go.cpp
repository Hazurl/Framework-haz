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
    using namespace haz;
    using namespace haz::Geometry2;
    using namespace haz::Geometry2::Collision;

    typedef Factory<GameObject> go_fact;
/*
    auto* _A = new GameObject("A");
    _A->addComponent<BoxCollider>(5, 5, 1, 1);

    go_fact::registerObject("A", _A);

    auto* g = go_fact::createObject("A");
    std::cout << g->getComponents().size() << std::endl;

    std::cout << g->to_string() << " -> " << g->getComponent<BoxCollider>()->position() << std::endl;

    Time time;

    Environement e;
    e.addGameObject(new GameObject("base"))->addComponent<BoxCollider>(-1, -1, 10, 8);
    e.addGameObject(new GameObject("a"))->addComponent<CircleCollider>(1, 0, 5);
    e.addGameObject(new GameObject("b"))->addComponent<BoxCollider>(0, 5, 4.5, 4.5);

    std::array<GameObject*, 5> gos;
    int count = Physic::raycast(&e, Vectorf{0, 0}, gos);

    if (count > 0) {
        for (GameObject* go : gos)
            if (--count >= 0)
                std::cout << "Hit : " << go->to_string() << std::endl;
    }
*/

    PolygonCollider p(nullptr, {
        {0, 0}, {1, 0}, {1, 1}, {0, 1}
    });
    
    std::cout << Vectorf{2, 0.5} << " : " << Collision::point_in_polygon(p, {2, 0.5}) << std::endl;
    std::cout << Vectorf{0, 0} << " : " << Collision::point_in_polygon(p, {0, 0}) << std::endl;
    std::cout << Vectorf{0, 1} << " : " << Collision::point_in_polygon(p, {0, 1}) << std::endl;
    std::cout << Vectorf{1, 0} << " : " << Collision::point_in_polygon(p, {1, 0}) << std::endl;
    std::cout << Vectorf{1, 1} << " : " << Collision::point_in_polygon(p, {1, 1}) << std::endl;
    std::cout << Vectorf{-1, 0.5} << " : " << Collision::point_in_polygon(p, {-1, 0.5}) << std::endl;
    std::cout << Vectorf{-2, 0.5} << " : " << Collision::point_in_polygon(p, {-2, 0.5}) << std::endl;
    std::cout << Vectorf{0.5, -1} << " : " << Collision::point_in_polygon(p, {0.5, -1}) << std::endl;
    std::cout << Vectorf{0.5, 0.5} << " : " << Collision::point_in_polygon(p, {0.5, 0.5}) << std::endl;
    std::cout << Vectorf{0, 0.5} << " : " << Collision::point_in_polygon(p, {0, 0.5}) << std::endl;
    std::cout << Vectorf{0.5, 0} << " : " << Collision::point_in_polygon(p, {0.5, 0}) << std::endl;
    

    return 0;
}