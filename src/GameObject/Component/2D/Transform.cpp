#include <GameObject/Component/2D/Transform.hpp>

BEG_NAMESPACE_HAZ_2D

Transform::Transform(GameObject* go) : Component(go), position(0, 0), scale(1, 1), rotation(0) {

}

Transform::Transform(GameObject* go, Vectorf const& position, Vectorf const& scale, float rotation) : Component(go), position(position), scale(scale), rotation(rotation) {

}

Transform::~Transform() {

}

Component* Transform::clone(GameObject* go) const {
    return new Transform(go, position, scale, rotation);
}

std::ostream& operator <<(std::ostream& os, Transform const& t) {
    os << "[position : " << t.position << ", rotation : " << t.rotation << ", scale : " << t.scale << "]";
    return os;
}

END_NAMESPACE_HAZ_2D