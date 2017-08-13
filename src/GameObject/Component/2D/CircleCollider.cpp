#include <GameObject/Component/2D/CircleCollider.hpp>

BEG_NAMESPACE_HAZ_2D

CircleCollider::CircleCollider(GameObject* go) : Collider(go) {
	
}

CircleCollider::CircleCollider(GameObject* go, float x, float y, float radius) : Collider(go), x(x), y(y), radius(radius) {
	
}

CircleCollider::CircleCollider(GameObject* go, Vectorf const& position, float radius) : Collider(go), x(position.x), y(position.y), radius(radius) {
	
}

CircleCollider::~CircleCollider() {
	
}

Component* CircleCollider::clone(GameObject* go) const {
    return new CircleCollider(go, x, y, radius);
}
/*
bool CircleCollider::colliding(Collider const* other) const {
    if (auto const* b = dynamic_cast<const BoxCollider*>(other)) {
        Vectorf dist = (position() - b->center()).abs();

        if (dist.x > (b->width / 2 + radius))
            return false;

        if (dist.y > (b->height / 2 + radius))
            return false;

        if (dist.x <= b->width / 2) 
            return true;

        if (dist.y <= b->height / 2) 
            return true;

        float dx = dist.x - b->width / 2;
        float dy = dist.y - b->height / 2;

        return dx * dx + dy * dy <= radius * radius;
    }
    if (auto const* c = dynamic_cast<const CircleCollider*>(other)) {
        return (position() - c->position()).magnitude2() <= radius * radius + c->radius * c->radius;
    }
    
    HAZ_ASSERT(false);
}

bool CircleCollider::colliding(Vectorf const& p) const {
    return (position() - p).magnitude2() <= radius * radius;
}
*/
END_NAMESPACE_HAZ_2D
