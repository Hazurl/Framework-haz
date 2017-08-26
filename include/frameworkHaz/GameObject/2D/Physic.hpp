#ifndef __HAZ_2D_PHYSIC
#define __HAZ_2D_PHYSIC

#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <frameworkHaz/GameObject/Environement.hpp>
#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

#include <frameworkHaz/GameObject/Component/2D/Transform.hpp>
#include <frameworkHaz/GameObject/Component/2D/BoxCollider.hpp>
#include <frameworkHaz/GameObject/Component/2D/CircleCollider.hpp>
#include <frameworkHaz/GameObject/Component/2D/EdgeCollider.hpp>
#include <frameworkHaz/GameObject/Component/2D/PolygonCollider.hpp>

BEG_NAMESPACE_HAZ_COLLISION

bool point_in_box(BoxCollider const& b, Vectorf point);
bool point_in_circle(CircleCollider const& c, Vectorf point);
bool point_in_polygon(PolygonCollider const& p, Vectorf point);
bool point_in_edge(EdgeCollider const& e, Vectorf point);
Vectorf getClosestPointInEdge(Vectorf const& a, Vectorf const& b, Vectorf const& point);
bool has_edge_intersection(Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d);
bool edge_intersection(Vectorf& result, Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d);

END_NAMESPACE_HAZ_COLLISION

BEG_NAMESPACE_HAZ_HIDDEN

void _test_Collision_Polygon();

END_NAMESPACE_HAZ_HIDDEN

BEG_NAMESPACE_HAZ_2D

class Physic {
public:

#define RAYCAST_SUB_BODY_A(T, F)\
for (auto* col : e->getComponents<T>()) {\
	if (col->getGO()->isOnAnyLayer(layers)) {\
		if (Collision::F(*col, point)) {\
			out[pos++] = col->getGO();\
			if (pos >= N)\
				return N;\
		}\
	}\
}

#define RAYCAST_BODY_A()\
std::size_t pos = 0;\
USING_NS_HAZ_COLLISION \
RAYCAST_SUB_BODY_A(BoxCollider, point_in_box)\
RAYCAST_SUB_BODY_A(CircleCollider, point_in_circle)\
RAYCAST_SUB_BODY_A(EdgeCollider, point_in_edge)\
RAYCAST_SUB_BODY_A(PolygonCollider, point_in_polygon)\
return pos;

#define RAYCAST_SUB_BODY_V(T, F)\
for (auto* col : e->getComponents<T>())\
	if (col->getGO()->isOnAnyLayer(layers))\
		if (Collision::F(*col, point))\
			gos.push_back(col->getGO());

#define RAYCAST_BODY_V()\
USING_NS_HAZ_COLLISION \
RAYCAST_SUB_BODY_V(BoxCollider, point_in_box)\
RAYCAST_SUB_BODY_V(CircleCollider, point_in_circle)\
RAYCAST_SUB_BODY_V(EdgeCollider, point_in_edge)\
RAYCAST_SUB_BODY_V(PolygonCollider, point_in_polygon)\
return gos;

	template<std::size_t N, typename = typename std::enable_if<(N > 0)>::type>
	static std::size_t raycast(Environement const* e, Vectorf const& point, std::array<const GameObject*, N>& out, Layers layers = Layers::All) {
		RAYCAST_BODY_A()
	}

	template<std::size_t N, typename = typename std::enable_if<(N > 0)>::type>
	static std::size_t raycast(Environement* e, Vectorf const& point, std::array<GameObject*, N>& out, Layers layers = Layers::All) {
		RAYCAST_BODY_A()
	}

	HAZ_FORCE_INLINE static bool raycast_any(Environement const* e, Vectorf const& point, Layers layers = Layers::All) {
		std::array<const GameObject*, 1> out = {};
		return raycast(e, point, out, layers) > 0;
	}

	static std::vector<const GameObject*> raycast_all(Environement const* e, Vectorf const& point, Layers layers = Layers::All) {
		std::vector<const GameObject*> gos = {};
		RAYCAST_BODY_V()	
	}

	static std::vector<GameObject*> raycast_all(Environement* e, Vectorf const& point, Layers layers = Layers::All) {
		std::vector<GameObject*> gos = {};
		RAYCAST_BODY_V()	
	}

	static GameObject* raycast_first(Environement* e, Vectorf const& point, Layers layers = Layers::All) {
		std::array<GameObject*, 1> out = {};
		raycast(e, point, out, layers);
		return raycast(e, point, out, layers) > 0 ? out[0] : nullptr;	
	}

	static const GameObject* raycast_first(Environement const* e, Vectorf const& point, Layers layers = Layers::All) {
		std::array<const GameObject*, 1> out = {};
		raycast(e, point, out, layers);
		return raycast(e, point, out, layers) > 0 ? out[0] : nullptr;	
	}
};

#undef RAYCAST_BODY
#undef RAYCAST_SUB_BODY

END_NAMESPACE_HAZ_2D

#endif