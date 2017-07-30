#include <System/Object.hpp>
#include <System/Wrapper.hpp>
#include <Container/DynamicArray.hpp>
#include <iostream>

int main (int argc, char ** argv) {
    haz::DynamicArray<haz::Int*> arr;
    arr.push(new haz::Int(42));
    std::cout << arr << std::endl;

    delete arr.remove(0);

    return 0;
}