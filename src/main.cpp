#include <System/Object.hpp>
#include <System/Wrapper.hpp>
#include <Container/DynamicArray.hpp>
#include <iostream>

namespace haz { class Test : public Object { public: Object::TString to_string () const { return "ok"; }};} 

int main (int argc, char ** argv) {
    haz::Int i = 0;
    std::cout << i.to_string() << std::endl;    
    int& _i = i.get();
    _i += 42;
    //i = _i;
    std::cout << i.to_string() << std::endl;    
    i += 42;
    std::cout << i.to_string() << std::endl;    

    return 0;
}