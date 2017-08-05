//#include <Benchmark/Benchmark.hpp>
#include <GameObject/GameObject.hpp>
#include <GameObject/Transform2D.hpp>
#include <Macro.hpp>
#include <EnumFlag.hpp>
#include <iostream>

int main (int , char ** ) {
    //haz::Benchmark::all();
    using namespace haz;
    using namespace haz::Geometry2;

    Time time;

    GameObject go;
    auto* c = go.addComponent<Transform2D>();
    c->setPosition(Vector<float>::up());
    c->setScale({0.5, 0.5});
    c->setRotation(50);

    std::cout << *c << std::endl;

    return 0;
}