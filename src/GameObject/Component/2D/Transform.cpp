#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>

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

std::string Transform::to_string () const {
    return "{ position : " + position.to_string() + ", rotation : " + std::to_string(rotation) + ", scale : " + scale.to_string() + " }";
}

std::ostream& operator <<(std::ostream& os, Transform const& t) {
    os << t.to_string();
    return os;
}

END_NAMESPACE_HAZ_2D