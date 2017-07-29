#include <System/Object.hpp>
#include <System/Wrapper.hpp>
#include <Container/DynamicArray.hpp>
#include <iostream>

namespace haz { class Test : public Object { public: Object::TString to_string () const { return "ok"; }};} 

auto& c () { return std::cout; }

int main (int argc, char ** argv) {
    haz::Int i = 12;
    haz::Double d = 0.1;
    
    //std::cout << ((int)12) + ((double)0.1) << std::endl;
    std::cout << i << std::endl;
    std::cout << i + d << std::endl;
    std::cout << d + i << std::endl;

    haz::ULLong res = d + i;
    int __i = d.value + i.value;
    std::cout << res << std::endl;

    std::cin >> i;
    std::cout << res + i << std::endl; 
    return 0;
}