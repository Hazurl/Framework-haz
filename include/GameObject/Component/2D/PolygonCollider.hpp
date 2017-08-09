#ifndef __HAZ_POLYGONCOLLIDER
#define __HAZ_POLYGONCOLLIDER

#include <GameObject/Component/2D/Collider.hpp>
#include <Tools/Utility.hpp>
#include <Tools/Macro.hpp>
#include <vector>
#include <Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_GEOM2

class PolygonCollider : public Collider {
public:
	PolygonCollider(GameObject* go, std::vector<Vectorf> const& points);
	~PolygonCollider();

	Component* clone(GameObject* go) const;

	std::vector<Vectorf> getPath() const;
	void setPath(std::vector<Vectorf> const& points);

private:

	std::vector<Vectorf> points;
};

END_NAMESPACE_HAZ_GEOM2

#endif