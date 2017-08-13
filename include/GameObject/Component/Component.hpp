#ifndef __HAZ_COMPONENT
#define __HAZ_COMPONENT

#include <Tools/Macro.hpp>
#include <Tools/Utility.hpp>
#include <Tools/Time.hpp>

BEG_NAMESPACE_HAZ

class GameObject;
class Environement;

class Component {
public:
    Component(GameObject* go);
    virtual ~Component() {};
    virtual Component* clone(GameObject* go) const = 0;

    GameObject* getGO ();
    const GameObject* getGO () const;

    virtual void update(Time const& t, Environement* e);

    virtual void onEnable();
    virtual void onDisable();
    
protected:

private:
    GameObject* go;
};

END_NAMESPACE_HAZ

#endif