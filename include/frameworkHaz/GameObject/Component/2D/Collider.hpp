#ifndef __HAZ_2D_COLLIDER
#define __HAZ_2D_COLLIDER

#include <frameworkHaz/GameObject/Component/Component.hpp>
#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_2D

class Collider : public Component {
public:
	Collider(GameObject* go);
	virtual ~Collider();

private:

};

END_NAMESPACE_HAZ_2D

#endif