#include <Container/DynamicArray.hpp>
#include <iostream>

int main (int , char ** ) {
    haz::DynamicArray<int> a;
    haz::DynamicArray<int> b;

    a.push(0);
    a.push(1);
    a.push(2);
    a.push(3);

    b = a;
    haz::DynamicArray<int> c = a;
    std::cout << "a : ";
    for(unsigned int i = 0; i < a.getSize(); ++i)
        std::cout << a[i] << ", ";
    std::cout << std::endl;
    std::cout << "c : ";
    for(unsigned int i = 0; i < c.getSize(); ++i)
        std::cout << c[i] << ", ";
    std::cout << std::endl;
    a.remove(0);
    std::cout << "a : ";
    for(unsigned int i = 0; i < a.getSize(); ++i)
        std::cout << a[i] << ", ";
    std::cout << std::endl;
    std::cout << "c : ";
    for(unsigned int i = 0; i < c.getSize(); ++i)
        std::cout << c[i] << ", ";
    std::cout << std::endl;
    std::cout << "b : ";
    for(unsigned int i = 0; i < c.getSize(); ++i)
        std::cout << c[i] << ", ";
    std::cout << std::endl;

    return 0;
}