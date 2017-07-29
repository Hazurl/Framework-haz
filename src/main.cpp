#include <System/Object.hpp>
#include <System/Wrapper.hpp>
#include <Container/DynamicArray.hpp>
#include <iostream>

int main (int argc, char ** argv) {
    haz::DynamicArray<haz::Int> arr;
    arr.push(42);
    std::cout << arr << std::endl;

    return 0;
}