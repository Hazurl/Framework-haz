#include <Component/2D/Transform.hpp>

BEG_NAMESPACE_HAZ_GEOM2

Transform::Transform(GameObject* go) : Component(go), position(0, 0), scale(1, 1), rotation(0) {

}

Transform::~Transform() {

}

std::ostream& operator <<(std::ostream& os, Transform const& t) {
    os << "[position : " << t.position << ", rotation : " << t.rotation << ", scale : " << t.scale << "]";
    return os;
}

END_NAMESPACE_HAZ_GEOM2