#ifndef __HAZ_COMPONENT
#define __HAZ_COMPONENT

#include <Macro.hpp>
#include <Utility.hpp>
#include <Tools/Time.hpp>

BEG_NAMESPACE_HAZ

class GameObject;

class Component {
public:
    virtual ~Component() {};

    GameObject* getGO ();
    const GameObject* getGO () const;

    void update(Time const& t);
    

protected:

private:
    friend class GameObject;
    GameObject* go = nullptr;

};

END_NAMESPACE_HAZ

#endif