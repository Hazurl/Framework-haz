#ifndef __HAZ_2D_CIRCLECOLLIDER
#define __HAZ_2D_CIRCLECOLLIDER

#include <haz/GameObject/Component/2D/Collider.hpp>
#include <haz/Tools/Utility.hpp>
#include <haz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ_2D

class CircleCollider : public Collider {
public:
	CircleCollider(GameObject* go);
	CircleCollider(GameObject* go, float x, float y, float radius);
	CircleCollider(GameObject* go, Vectorf const& position, float radius);

	~CircleCollider();

	std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
	
	Component* clone(GameObject* go) const;
	
	HAZ_FORCE_INLINE Vectorf position() const { return {x, y}; }

	float x, y, radius;
};

END_NAMESPACE_HAZ_2D

#endif