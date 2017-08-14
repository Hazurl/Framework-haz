#include <frameworkHaz/GameObject/Component/2D/BoxCollider.hpp>

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

Component* BoxCollider::clone(GameObject* go) const {
    return new BoxCollider(go, x, y, width, height);
}
/*
bool BoxCollider::colliding(Collider const* other) const {
    if (auto const* b = dynamic_cast<const BoxCollider*>(other)) {
        return  !(   right() > b->left()
                ||   left() < b->right()
                ||   top() < b->bottom()
                ||   bottom() < b->top() );
    }
    if (auto const* c = dynamic_cast<const CircleCollider*>(other)) {
        Vectorf dist = (c->position() - center()).abs();

        if (dist.x > (width / 2 + c->radius))
            return false;

        if (dist.y > (height / 2 + c->radius))
            return false;

        if (dist.x <= width / 2) 
            return true;

        if (dist.y <= height / 2) 
            return true;

        float dx = dist.x - width / 2;
        float dy = dist.y - height / 2;

        return dx * dx + dy * dy <= c->radius * c->radius;
    }
    
    HAZ_ASSERT(false);
}

bool BoxCollider::colliding(Vectorf const& p) const {
    return haz::between_ii(p.x, left(), right()) 
        && haz::between_ii(p.y, top(), bottom());
}
*/
END_NAMESPACE_HAZ_2D
