#include <GameObject/Component/2D/PolygonCollider.hpp>

BEG_NAMESPACE_HAZ_GEOM2

PolygonCollider::~PolygonCollider() {
	
}

PolygonCollider::PolygonCollider(GameObject* go, std::vector<Vectorf> const& points) : Collider(go), points(points) {
    HAZ_ASSERT(points.size() > 2);
}

Component* PolygonCollider::clone(GameObject* go) const {
    return new PolygonCollider(go, points);
}

std::vector<Vectorf> PolygonCollider::getPath() const {
    return points;
}

void PolygonCollider::setPath(std::vector<Vectorf> const& points) {
    HAZ_ASSERT(points.size() > 2);
    this->points = points;
}

END_NAMESPACE_HAZ_GEOM2