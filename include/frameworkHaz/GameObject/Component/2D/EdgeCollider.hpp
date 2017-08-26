#ifndef __HAZ_EDGECOLLIDER
#define __HAZ_EDGECOLLIDER

#include <frameworkHaz/GameObject/Component/2D/Collider.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Tools/Macro.hpp>
#include <vector>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class EdgeCollider : public Collider {
public:
	EdgeCollider(GameObject* go, std::vector<Vectorf> const& points, float radius = 0);
	~EdgeCollider();

	std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
	
	Component* clone(GameObject* go) const;

	std::vector<Vectorf> points;
	float radius;
};

END_NAMESPACE_HAZ_2D

#endif