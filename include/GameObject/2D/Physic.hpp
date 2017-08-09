#ifndef __HAZ_2D_PHYSIC
#define __HAZ_2D_PHYSIC

#include <Tools/Macro.hpp>
#include <Tools/Utility.hpp>
#include <GameObject/Environement.hpp>
#include <GameObject/GameObject.hpp>
#include <Geometry/2D/Vector.hpp>

#include <GameObject/Component/2D/BoxCollider.hpp>
#include <GameObject/Component/2D/CircleCollider.hpp>
#include <GameObject/Component/2D/EdgeCollider.hpp>
#include <GameObject/Component/2D/PolygonCollider.hpp>

BEG_NAMESPACE_HAZ_GEOM2

namespace Collision {

bool point_in_box(BoxCollider const& b, Vectorf const& point);
bool point_in_circle(CircleCollider const& c, Vectorf const& point);
bool point_in_polygon(PolygonCollider const& p, Vectorf const& point);
bool point_in_edge(EdgeCollider const& e, Vectorf const& point);
Vectorf getClosestPointInEdge(Vectorf const& a, Vectorf const& b, Vectorf const& point);
bool has_edge_intersection(Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d);
bool edge_intersection(Vectorf& result, Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d);

}

class Physic {
public:

	template<std::size_t N, typename = typename std::enable_if<(N > 0)>::type>
	static std::size_t raycast(Environement const* e, Geometry2::Vectorf const& point, std::array<const GameObject*, N>& out, Layers layers = Layers::All) {
		std::size_t pos = 0;
		for (auto* col : e->getComponents<Collider>()) {
			if (col->getGO()->isOnAnyLayer(layers)) {
				/*if (col->colliding(point)) {
					out[pos++] = col->getGO();
					if (pos >= N)
						return N;
				}*/
			}
		}

		return pos;
	}

	template<std::size_t N, typename = typename std::enable_if<(N > 0)>::type>
	static std::size_t raycast(Environement* e, Geometry2::Vectorf const& point, std::array<GameObject*, N>& out, Layers layers = Layers::All) {
		std::size_t pos = 0;
		for (auto* col : e->getComponents<Collider>()) {
			if (col->getGO()->isOnAnyLayer(layers)) {
				/*if (col->colliding(point)) {
					out[pos++] = col->getGO();
					if (pos >= N)
						return N;
				}*/
			}
		}

		return pos;
	}

	inline static bool raycast_any(Environement const* e, Geometry2::Vectorf const& point, Layers layers = Layers::All) {
		std::array<const GameObject*, 1> out = {};
		return raycast(e, point, out, layers) > 0;
	}

};

END_NAMESPACE_HAZ_GEOM2

#endif