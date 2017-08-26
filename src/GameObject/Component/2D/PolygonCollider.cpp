#include <frameworkHaz/GameObject/Component/2D/PolygonCollider.hpp>

BEG_NAMESPACE_HAZ_2D

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

std::string PolygonCollider::to_string() const {
    std::string s = "{";

    for (auto& p : points) {
        s += " " + p.to_string();
    }

    return s + " }";
}

std::vector<std::string> PolygonCollider::pretty_strings() const {
    std::vector<std::string> v {
        "Points (" + std::to_string(points.size()) + "):",
    };

    for (auto& p : points) {
        v.push_back(" " + p.to_string());
    }

    return v;
}

END_NAMESPACE_HAZ_2D