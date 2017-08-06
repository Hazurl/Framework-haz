#ifndef __HAZ_2D_BOXCOLLIDER
#define __HAZ_2D_BOXCOLLIDER

#include <Component/2D/Collider.hpp>
#include <Utility.hpp>
#include <Macro.hpp>

BEG_NAMESPACE_HAZ_GEOM2

class BoxCollider : public Collider {
public:
	BoxCollider(GameObject* go);
	BoxCollider(GameObject* go, float x, float y, float width, float height);
	BoxCollider(GameObject* go, Vectorf const& position, float width, float height);
	BoxCollider(GameObject* go, Vectorf const& position, Vectorf const& size);

	~BoxCollider();

	bool colliding_with(Collider const* other) const;
	bool colliding_with(Vectorf const& points) const;

private:
	float x, y, width, height;
};

END_NAMESPACE_HAZ_GEOM2

#endif