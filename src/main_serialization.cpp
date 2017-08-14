/*#include <frameworkHaz/Serialization/Serializer.hpp>

#include <string>

class Obj : public haz::serialization::Serializable {
public:
    int i = 42;
    long j = 1000;

    std::string s = "ok";

    template<typename Archive>
    void serialize(Archive& a) {
        a & i & j & s;
    }
};
*/
int main (int, char**) {
/*    USING_NS_HAZ
    USING_NS_HAZ_SERIALIZATION
    
    {
        int i = 42;
        int j = 0;
        Serializer s;

        s << i;
        s >> j;
        std::cout << i << "->" << j << std::endl;    
        std::cout << s.get() << std::endl;
    }
    {
        Obj o;
        Serializer s;

        s << o;
        o.i--;
        o.j--;
        o.s += ".";
        s >> o;

        std::cout << o.i << ", " << o.j << ", " << o.s << std::endl;
        std::cout << s.get() << std::endl;
    }
*/
    return 0;
}