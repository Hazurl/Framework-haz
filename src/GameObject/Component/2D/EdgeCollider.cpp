#include <haz/GameObject/Component/2D/EdgeCollider.hpp>

BEG_NAMESPACE_HAZ_2D

EdgeCollider::EdgeCollider(GameObject* go, std::vector<Vectorf> const& points, float radius) : Collider(go), points(points), radius(radius) {
	
}

EdgeCollider::~EdgeCollider() {
	
}

Component* EdgeCollider::clone(GameObject* go) const {
    return new EdgeCollider(go, points, radius);
}

std::string EdgeCollider::to_string() const {
    std::string s = "{";

    for (auto& p : points) {
        s += " " + p.to_string();
    }

    return s + " by " + std::to_string(radius) + " }";
}

std::vector<std::string> EdgeCollider::pretty_strings() const {
    std::vector<std::string> v {
        "Radius " + std::to_string(radius),
        "Points (" + std::to_string(points.size()) + "):",
    };

    for (auto& p : points) {
        v.push_back(" " + p.to_string());
    }

    return v;
}

END_NAMESPACE_HAZ_2D