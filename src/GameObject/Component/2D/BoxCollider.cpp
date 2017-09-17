#include <haz/GameObject/Component/2D/BoxCollider.hpp>

BEG_NAMESPACE_HAZ_2D

BoxCollider::BoxCollider(GameObject* go) : Collider(go) {
	
}

BoxCollider::BoxCollider(GameObject* go, float x, float y, float width, float height) : Collider(go), x(x), y(y), width(width), height(height) {
	
}

BoxCollider::BoxCollider(GameObject* go, Vectorf const& position, float width, float height) : Collider(go), x(position.x), y(position.y), width(width), height(height) {
	
}

BoxCollider::BoxCollider(GameObject* go, Vectorf const& position, Vectorf const& size) : Collider(go), x(position.x), y(position.y), width(size.x), height(size.y) {
	
}

BoxCollider::~BoxCollider() {
	
}

std::string BoxCollider::to_string() const {
    return "{ (" + std::to_string(x) + ", " + std::to_string(y) + ") by (" + std::to_string(width) + ", " + std::to_string(height) + ") }";
}

Component* BoxCollider::clone(GameObject* go) const {
    return new BoxCollider(go, x, y, width, height);
}

std::vector<std::string> BoxCollider::pretty_strings() const {
    return {
        "Position (" + std::to_string(x) + ", " + std::to_string(y) + ")",
        "Size (" + std::to_string(width) + ", " + std::to_string(height) + ")",
    };
}

END_NAMESPACE_HAZ_2D
