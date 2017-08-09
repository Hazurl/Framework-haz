#ifndef __HAZ_2D_COLLIDER
#define __HAZ_2D_COLLIDER

#include <GameObject/Component/Component.hpp>
#include <Tools/Macro.hpp>
#include <Tools/Utility.hpp>
#include <Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_GEOM2

class Collider : public Component {
public:
	Collider(GameObject* go);
	virtual ~Collider();

private:

};

END_NAMESPACE_HAZ_GEOM2

#endif