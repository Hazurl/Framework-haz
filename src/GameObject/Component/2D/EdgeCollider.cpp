#include <GameObject/Component/2D/EdgeCollider.hpp>

BEG_NAMESPACE_HAZ_2D

EdgeCollider::EdgeCollider(GameObject* go, std::vector<Vectorf> const& points, float radius) : Collider(go), points(points), radius(radius) {
	
}

EdgeCollider::~EdgeCollider() {
	
}

Component* EdgeCollider::clone(GameObject* go) const {
    return new EdgeCollider(go, points, radius);
}

END_NAMESPACE_HAZ_2D