#ifndef __HAZ_EDGECOLLIDER
#define __HAZ_EDGECOLLIDER

#include <GameObject/Component/2D/Collider.hpp>
#include <Tools/Utility.hpp>
#include <Tools/Macro.hpp>
#include <vector>
#include <Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class EdgeCollider : public Collider {
public:
	EdgeCollider(GameObject* go, std::vector<Vectorf> const& points, float radius = 0);
	~EdgeCollider();

	Component* clone(GameObject* go) const;

	std::vector<Vectorf> points;
	float radius;
};

END_NAMESPACE_HAZ_2D

#endif