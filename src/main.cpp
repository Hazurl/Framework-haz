//#include <Benchmark/Benchmark.hpp>
#include <GameObject/GameObject.hpp>
#include <Tools/Environement.hpp>
#include <Geometry/2D/Physic.hpp>
#include <Component/2D/Transform.hpp>
#include <Component/2D/BoxCollider.hpp>
#include <Macro.hpp>
#include <iostream>

int main (int , char ** ) {
    //haz::Benchmark::all();
    using namespace haz;
    using namespace haz::Geometry2;

    Time time;

    Environement e;
    e.addGameObject(new GameObject("base"));

    e.find_GO_of_name("base")->addComponent<BoxCollider, Collider>(0, 0, 1, 1);

    e.addGameObject(new GameObject("a"));

    e.find_GO_of_name("a")->addComponent<BoxCollider, Collider>(-1, -1, 1, 1);

    e.addGameObject(new GameObject("b"));

    e.find_GO_of_name("b")->addComponent<BoxCollider, Collider>(-1, -1, 5, 1);

    for (auto* go : Physic::rayCast(&e, Vectorf{.5, .5})) {
        std::cout << "Hit : " << go->to_string() << std::endl;
    }

    return 0;
}