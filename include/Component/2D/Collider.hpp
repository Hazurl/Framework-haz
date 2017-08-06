#ifndef __HAZ_2D_COLLIDER
#define __HAZ_2D_COLLIDER

#include <Component/Component.hpp>
#include <Macro.hpp>
#include <Utility.hpp>
#include <Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_GEOM2

class Collider : public Component {
public:
	Collider(GameObject* go);
	virtual ~Collider();

	virtual bool colliding_with(Collider const* other) const = 0;
	virtual bool colliding_with(Vectorf const& points) const = 0;

private:

};

END_NAMESPACE_HAZ_GEOM2

#endif