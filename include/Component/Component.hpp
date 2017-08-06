#ifndef __HAZ_COMPONENT
#define __HAZ_COMPONENT

#include <Macro.hpp>
#include <Utility.hpp>
#include <Tools/Time.hpp>

BEG_NAMESPACE_HAZ

class GameObject;
class Environement;

class Component {
public:
    Component(GameObject* go);
    virtual ~Component() {};

    GameObject* getGO ();
    const GameObject* getGO () const;

    void update(Time const& t, Environement* e);

protected:

private:
    GameObject* go;
};

END_NAMESPACE_HAZ

#endif