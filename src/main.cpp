#include <Container/DynamicArray.hpp>
#include <iostream>

int main (int , char ** ) {
    haz::DynamicArray<int> a;
    haz::DynamicArray<int> b;

    a.push(0);
    a.push(1);
    a.push(2);
    a.push(3);
    a.push({4, 5, 6, 7, 8, 9});

    b = a;
    haz::DynamicArray<int> c = a;
    b.push({42, 0, 1, 2, 3});
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
    for(unsigned int i = 0; i < b.getSize(); ++i)
        std::cout << b[i] << ", ";
    std::cout << std::endl;
    b.resize(12, 100);
    std::cout << "b : ";
    for(unsigned int i = 0; i < b.getSize(); ++i)
        std::cout << b[i] << ", ";
    std::cout << std::endl;
    b.resize(10, 100);
    std::cout << "b : ";
    for(unsigned int i = 0; i < b.getSize(); ++i)
        std::cout << b[i] << ", ";
    std::cout << std::endl;
    std::cout << b.getCapacity() << std::endl;
    b.reserve(15);
    std::cout << b.getCapacity() << std::endl;
    std::cout << "b : ";
    for(unsigned int i = 0; i < b.getSize(); ++i)
        std::cout << b[i] << ", ";
    std::cout << std::endl;
    b.reserve(5);
    std::cout << "b : ";
    for(unsigned int i = 0; i < b.getSize(); ++i)
        std::cout << b[i] << ", ";
    std::cout << std::endl;
    a.insert(2, 50);
    a.insert(2, 51);
    a.insert(2, 52);
    std::cout << "a : ";
    for(unsigned int i = 0; i < a.getSize(); ++i)
        std::cout << a[i] << ", ";
    std::cout << std::endl;
    std::cout << "Pop : " << a.pop_back() << std::endl;
    std::cout << "Pop : " << a.pop_back() << std::endl;
    std::cout << "Pop : " << a.pop_back() << std::endl;
    std::cout << "Pop 2 : " << a.pop(2) << std::endl;
    std::cout << "a : ";
    for(unsigned int i = 0; i < a.getSize(); ++i)
        std::cout << a[i] << ", ";
    std::cout << std::endl;
    for(int& v : a)
        std::cout << v << ", ";
    std::cout << std::endl;



    return 0;
}