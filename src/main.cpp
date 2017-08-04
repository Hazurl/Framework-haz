//#include <Benchmark/Benchmark.hpp>
#include <GameObject/GameObject.hpp>
#include <GameObject/Transform2D.hpp>
#include <Macro.hpp>
#include <EnumFlag.hpp>
#include <iostream>

int main (int , char ** ) {
    //haz::Benchmark::all();
    using namespace haz;

    GameObject go;
    //go.addComponent<Transform2D>();
    go.addComponent<Transform2D>(0, 1);

    return 0;
}