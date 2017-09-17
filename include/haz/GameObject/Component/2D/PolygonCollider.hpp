#ifndef __HAZ_POLYGONCOLLIDER
#define __HAZ_POLYGONCOLLIDER

#include <haz/GameObject/Component/2D/Collider.hpp>
#include <haz/Tools/Utility.hpp>
#include <haz/Tools/Macro.hpp>
#include <vector>
#include <haz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class PolygonCollider : public Collider {
public:
	PolygonCollider(GameObject* go, std::vector<Vectorf> const& points);
	~PolygonCollider();

	std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
	
	Component* clone(GameObject* go) const;

	std::vector<Vectorf> getPath() const;
	void setPath(std::vector<Vectorf> const& points);

private:

	std::vector<Vectorf> points;
};

END_NAMESPACE_HAZ_2D

#endif