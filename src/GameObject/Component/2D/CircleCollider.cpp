#include <frameworkHaz/GameObject/Component/2D/CircleCollider.hpp>

BEG_NAMESPACE_HAZ_2D

CircleCollider::CircleCollider(GameObject* go) : Collider(go) {
	
}

CircleCollider::CircleCollider(GameObject* go, float x, float y, float radius) : Collider(go), x(x), y(y), radius(radius) {
	
}

CircleCollider::CircleCollider(GameObject* go, Vectorf const& position, float radius) : Collider(go), x(position.x), y(position.y), radius(radius) {
	
}

CircleCollider::~CircleCollider() {
	
}

std::string CircleCollider::to_string() const {
    return "{ (" + std::to_string(x) + ", " + std::to_string(y) + ") by " + std::to_string(radius) + " }";
}

Component* CircleCollider::clone(GameObject* go) const {
    return new CircleCollider(go, x, y, radius);
}

std::vector<std::string> CircleCollider::pretty_strings() const {
    return {
        "Position (" + std::to_string(x) + ", " + std::to_string(y) + ")",
        "Radius " + std::to_string(radius)
    };
}

END_NAMESPACE_HAZ_2D
