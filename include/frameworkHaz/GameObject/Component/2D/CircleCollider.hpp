#ifndef __HAZ_2D_CIRCLECOLLIDER
#define __HAZ_2D_CIRCLECOLLIDER

#include <frameworkHaz/GameObject/Component/2D/Collider.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ_2D

class CircleCollider : public Collider {
public:
	CircleCollider(GameObject* go);
	CircleCollider(GameObject* go, float x, float y, float radius);
	CircleCollider(GameObject* go, Vectorf const& position, float radius);

	~CircleCollider();

	Component* clone(GameObject* go) const;
	
	HAZ_FORCE_INLINE Vectorf position() const { return {x, y}; }

	float x, y, radius;
};

END_NAMESPACE_HAZ_2D

#endif