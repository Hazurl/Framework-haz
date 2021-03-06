#include <haz/GameObject/Component/2D/Transform.hpp>

BEG_NAMESPACE_HAZ_2D

Transform::Transform(GameObject* go) : Component(go), pos(0, 0), sca(1, 1), rot(0) {

}

Transform::Transform(GameObject* go, Vectorf const& pos, Vectorf const& sca, float rot) : Component(go), pos(pos), sca(sca), rot(rot) {

}

Transform::~Transform() {

}

Vectorf Transform::position() const {
    return pos;
}

Vectorf Transform::globalPosition() const {
    auto* parent = gameobject()->parent();
    
    return parent == nullptr ? position() : position() + parent->transform()->globalPosition();
}

Vectorf Transform::scale() const {
    return sca;
}

Vectorf Transform::globalScale() const {
    auto* parent = gameobject()->parent();
    
    return parent == nullptr ? scale() : scale() * parent->transform()->globalScale();
}

float Transform::rotation() const {
    return rot;
}

float Transform::globalRotation() const {
    auto* parent = gameobject()->parent();
    
    return parent == nullptr ? rotation() : rotation() + parent->transform()->globalRotation();
}

void Transform::position(Vectorf const& p) {
    pos = p;
}

void Transform::globalPosition(Vectorf const& p) {
    pos = globalPosition() - position() + p;
}

void Transform::scale(Vectorf const& s) {
    sca = s;
}

void Transform::globalScale(Vectorf const& s) {
    auto* parent = gameobject()->parent();
    sca = parent == nullptr ? s : (s / parent->transform()->globalScale());
}

void Transform::rotation(float r) {
    rot = r;
}

void Transform::globalRotation(float r) {
    rot = globalRotation() - rotation() + r;
}

Component* Transform::clone(GameObject* go) const {
    return new Transform(go, pos, sca, rot);
}

std::string Transform::to_string () const {
    return "{ position : " + pos.to_string() + ", rotation : " + std::to_string(rot) + ", scale : " + sca.to_string() + " }";
}

std::vector<std::string> Transform::pretty_strings() const {
    return {
        "Position " + pos.to_string(),
        "Rotation " + std::to_string(rot),
        "Scale " + sca.to_string()
    };
}

std::ostream& operator <<(std::ostream& os, Transform const& t) {
    os << t.to_string();
    return os;
}

void Transform::onEnable() {}
void Transform::onDisable() {}


END_NAMESPACE_HAZ_2D