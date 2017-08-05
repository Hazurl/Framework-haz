#include <GameObject/Transform2D.hpp>

BEG_NAMESPACE_HAZ

Transform2D::Transform2D() : position(0, 0), scale(1, 1), rotation(0) {

}

Transform2D::~Transform2D() {

}

Vector2<float> Transform2D::getPosition () const {
    return position;
}

Vector2<float> Transform2D::getScale () const {
    return scale;
}

float Transform2D::getRotation () const {
    return rotation;
}

void Transform2D::setPosition (Vector2<float> const& p) {
    this->position = p;
}

void Transform2D::setScale (Vector2<float> const& s) {
    this->scale = s;
}

void Transform2D::setRotation (float r) {
    rotation = r;
}

std::ostream& operator <<(std::ostream& os, Transform2D const& t) {
    os << "[position : " << t.position << ", rotation : " << t.rotation << ", scale : " << t.scale << "]";
    return os;
}

END_NAMESPACE_HAZ