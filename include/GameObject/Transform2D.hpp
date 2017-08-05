#ifndef __HAZ_TRANFORM2D
#define __HAZ_TRANFORM2D

#include <GameObject/Component.hpp>
#include <Macro.hpp>
#include <Utility.hpp>
#include <Tools/Vector2.hpp>

BEG_NAMESPACE_HAZ

class Transform2D : public Component {
public:
    Transform2D();
    ~Transform2D();

    Vector2<float> getPosition () const;
    Vector2<float> getScale () const;
    float getRotation () const;

    void setPosition (Vector2<float> const& p);
    void setScale (Vector2<float> const& s);
    void setRotation (float r);

    friend std::ostream& operator <<(std::ostream& os, Transform2D const& t);

private:
    Vector2<float> position;
    Vector2<float> scale;
    float rotation;
};

END_NAMESPACE_HAZ

#endif