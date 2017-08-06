#include <Geometry/2D/Physic.hpp>

BEG_NAMESPACE_HAZ_GEOM2

std::vector<GameObject*> Physic::rayCast(Environement* e, Geometry2::Vectorf const& point, Layer layers) {
    using namespace haz::Geometry2;
    
    std::vector<GameObject*> go_hit = {};

    // TODO : don't be dumb

    for (auto* col : e->getComponents<Collider>())
        if (col->getGO()->isOnLayer(layers))
            if (col->colliding_with(point))
                go_hit.push_back(col->getGO());

    return go_hit;
}

std::vector<const GameObject*> Physic::rayCast(Environement const* e, Geometry2::Vectorf const& point, Layer layers) {
    using namespace haz::Geometry2;
    
    std::vector<const GameObject*> go_hit = {};

    // TODO : don't be dumb

    for (const auto* col : e->getComponents<Collider>())
        if (col->getGO()->isOnLayer(layers))
            if (col->colliding_with(point))
                go_hit.push_back(col->getGO());

    return go_hit;
}

END_NAMESPACE_HAZ_GEOM2