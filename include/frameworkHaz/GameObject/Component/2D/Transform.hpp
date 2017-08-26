#ifndef __HAZ_2D_TRANFORM
#define __HAZ_2D_TRANFORM

#include <frameworkHaz/GameObject/Component/Component.hpp>
#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class Transform : public Component {
public:
    Transform(GameObject* go);
    Transform(GameObject* go, Vectorf const& pos, Vectorf const& sca, float rot);
    ~Transform();

    std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
    
    Component* clone(GameObject* go) const;

    friend std::ostream& operator <<(std::ostream& os, Transform const& t);

    Vectorf position() const;
    Vectorf globalPosition() const;

    Vectorf scale() const;
    Vectorf globalScale() const;

    float rotation() const;
    float globalRotation() const;

    void position(Vectorf const& p);
    void globalPosition(Vectorf const& p);

    void scale(Vectorf const& s);
    void globalScale(Vectorf const& s);

    void rotation(float r);
    void globalRotation(float r);

private:
    Vectorf pos;
    Vectorf sca;
    float rot;
};

END_NAMESPACE_HAZ_2D

#endif