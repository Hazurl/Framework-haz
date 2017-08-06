#ifndef __HAZ_2D_TRANFORM
#define __HAZ_2D_TRANFORM

#include <Component/Component.hpp>
#include <Macro.hpp>
#include <Utility.hpp>
#include <Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_GEOM2

using namespace Geometry2;

class Transform : public Component {
public:
    Transform(GameObject* go);
    ~Transform();

    friend std::ostream& operator <<(std::ostream& os, Transform const& t);

    Vectorf position;
    Vectorf scale;
    float rotation;
};

END_NAMESPACE_HAZ_GEOM2

#endif