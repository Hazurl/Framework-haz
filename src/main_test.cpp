#include <haz/Benchmark/Benchmark.hpp>

#include <haz/Event/StaticDispatcher.hpp>
#include <haz/Tools/TypeHelper.hpp>

#include <haz/Tools/Macro.hpp>
#include <haz/Tools/SourceInfo.hpp>

#include <functional>

struct myEvent {
    int i;

    myEvent(int i) : i(i) {}
};

struct EvtA {
    int z;
    EvtA(int z) : z(z) {}
};

struct EvtB {
    int w;
    EvtB(int w) : w(w) {}
};

struct myClass {
    void receive(myEvent const& e) {
        std::cout << e.i << " ! " << std::endl;
    }

    void receive(EvtA const& e) {
        std::cout << e.z << " $" << std::endl;
    }

    void on(EvtB const& e) {
        std::cout << e.w << " £" << std::endl;
    }
    int z = 0;
};

int main(int /* argc */, char** /* argv */) {
    USING_NS_HAZ;

    evt::StaticDispatcher<myEvent, EvtA, EvtB> ed;
/*
    ed.subscribe<myEvent>([] (myEvent const& e) -> void {
        std::cout << "Receive : " << e.i << std::endl;
    });

    std::function<void(myEvent const&)> f = [] (myEvent const& e) {
        std::cout << "! " << e.i << std::endl;
    };
    ed.subscribe<myEvent>(f);
*/
    myClass m;  

    ed.subscribe_all(&m);
  
    ed.emit<myEvent>(42);
    ed.emit<EvtA>(1337);
    ed.emit<EvtB>(1337);
    
    return 0;
}