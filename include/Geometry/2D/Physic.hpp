#ifndef __HAZ_PHYSIC
#define __HAZ_PHYSIC

#include <Macro.hpp>
#include <Tools/Environement.hpp>
#include <GameObject/GameObject.hpp>
#include <Geometry/2D/Vector.hpp>

BEG_NAMESPACE_HAZ_GEOM2

class Physic {
public:

	static std::vector<GameObject*> rayCast(Environement* e, Geometry2::Vectorf const& point, Layer layers = Layer::All);
	static std::vector<const GameObject*> rayCast(Environement const* e, Geometry2::Vectorf const& point, Layer layers = Layer::All);

};

END_NAMESPACE_HAZ_GEOM2

#endif