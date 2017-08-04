#ifndef __HAZ_TRANFORM2D
#define __HAZ_TRANFORM2D

#include <GameObject/Component.hpp>
#include <Macro.hpp>
#include <Utility.hpp>

BEG_NAMESPACE_HAZ

class Transform2D : public Component {
public:
    Transform2D() : x(0), y(0) {}
    Transform2D(float x, float y) : x(x), y(y) {}

    ~Transform2D() {}

private:
    float x, y;
};

END_NAMESPACE_HAZ

#endif