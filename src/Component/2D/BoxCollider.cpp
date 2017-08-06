#include <Component/2D/BoxCollider.hpp>

BEG_NAMESPACE_HAZ_GEOM2

BoxCollider::BoxCollider(GameObject* go) : Collider(go) {
	
}

BoxCollider::BoxCollider(GameObject* go, float x, float y, float width, float height) : Collider(go), x(x), y(y), width(width), height(height) {
	
}

BoxCollider::BoxCollider(GameObject* go, Vectorf const& position, float width, float height) : Collider(go), x(position.getX()), y(position.getY()), width(width), height(height) {
	
}

BoxCollider::BoxCollider(GameObject* go, Vectorf const& position, Vectorf const& size) : Collider(go), x(position.getX()), y(position.getY()), width(size.getX()), height(size.getY()) {
	
}

BoxCollider::~BoxCollider() {
	
}

bool BoxCollider::colliding_with(Collider const* other) const {
    if (auto* o = dynamic_cast<const BoxCollider*>(other)) {
        return !(   x > o->x + o->width
               ||   x + width < o->x
               ||   y > o->y + o->height
               ||   y + height < o->y );
    }

    HAZ_ASSERT(false);
}

bool BoxCollider::colliding_with(Vectorf const& points) const {
    return haz::between_ii(points.getX(), x, x + width) && haz::between_ii(points.getY(), y, y + height);
}

END_NAMESPACE_HAZ_GEOM2
