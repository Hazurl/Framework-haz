#ifndef __HAZ_POLYGONCOLLIDER
#define __HAZ_POLYGONCOLLIDER

#include <frameworkHaz/GameObject/Component/2D/Collider.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Tools/Macro.hpp>
#include <vector>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class PolygonCollider : public Collider {
public:
	PolygonCollider(GameObject* go, std::vector<Vectorf> const& points);
	~PolygonCollider();

	std::string to_string() const;
	
	Component* clone(GameObject* go) const;

	std::vector<Vectorf> getPath() const;
	void setPath(std::vector<Vectorf> const& points);

private:

	std::vector<Vectorf> points;
};

END_NAMESPACE_HAZ_2D

#endif