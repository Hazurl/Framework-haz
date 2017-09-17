#ifndef __HAZ_2D_COLLIDER
#define __HAZ_2D_COLLIDER

#include <haz/GameObject/GameObject.hpp>
#include <haz/Tools/Macro.hpp>
#include <haz/Tools/Utility.hpp>
#include <haz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class Collider : public Component {
public:
	Collider(GameObject* go);
	virtual ~Collider();

private:

};

END_NAMESPACE_HAZ_2D

#endif