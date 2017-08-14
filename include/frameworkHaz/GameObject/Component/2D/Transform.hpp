#ifndef __HAZ_2D_TRANFORM
#define __HAZ_2D_TRANFORM

#include <frameworkHaz/GameObject/Component/Component.hpp>
#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class Transform : public Component {
public:
    Transform(GameObject* go);
    Transform(GameObject* go, Vectorf const& position, Vectorf const& scale, float rotation);
    ~Transform();

	Component* clone(GameObject* go) const;

    friend std::ostream& operator <<(std::ostream& os, Transform const& t);

    Vectorf position;
    Vectorf scale;
    float rotation;
};

END_NAMESPACE_HAZ_2D

#endif