#ifndef __HAZ_2D_TRANFORM
#define __HAZ_2D_TRANFORM

#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>

#include <frameworkHaz/Geometry/2D/Vector.hpp>

#include <frameworkHaz/GameObject/GameObject.hpp>

#include <vector>
#include <string>

BEG_NAMESPACE_HAZ_2D

class Transform : public Component {
public:
    /* Ctor Dtor */
    Transform(GameObject* go);
    Transform(GameObject* go, Vectorf const& pos, Vectorf const& sca, float rot);
    ~Transform();

    Component* clone(GameObject* go) const;
    
    /* Stringify */
    std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
    
    friend std::ostream& operator <<(std::ostream& os, Transform const& t);
    
    /* Position */
    Vectorf position() const;
    void position(Vectorf const& p);
    Vectorf globalPosition() const;
    void globalPosition(Vectorf const& p);

    /* Scale */
    Vectorf scale() const;
    void scale(Vectorf const& s);
    Vectorf globalScale() const;
    void globalScale(Vectorf const& s);
    
    /* Rotation */
    float rotation() const;
    void rotation(float r);
    float globalRotation() const;
    void globalRotation(float r);

    /* Component Implementation */
    void onEnable();
    void onDisable();

private:
    Vectorf pos;
    Vectorf sca;
    float rot;
};

END_NAMESPACE_HAZ_2D

#endif