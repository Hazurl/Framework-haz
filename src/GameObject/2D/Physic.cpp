#include <GameObject/2D/Physic.hpp>

BEG_NAMESPACE_HAZ_GEOM2

namespace Collision {

bool point_in_box(BoxCollider const& b, Vectorf const& point) {
    return haz::between_ii(point.getX(), b.left(), b.right()) 
        && haz::between_ii(point.getY(), b.top(), b.bottom());
}

bool point_in_circle(CircleCollider const& c, Vectorf const& point) {
    return (c.position() - point).magnitude2() <= c.radius * c.radius;
}

bool point_in_polygon(PolygonCollider const& p, Vectorf const& point) {
    auto points = p.getPath();
    auto last = points[points.size() - 1];

    bool res = false;
    for (unsigned int pos = 0; pos < points.size(); ++pos) {
        auto cur = points[pos];

        if ((cur.getY() <= point.getY()) && (last.getY() >= point.getY()) || (last.getY() <= point.getY()) && (cur.getY() >= point.getY())) {
            auto deno = last.getY() - cur.getY();
            if (deno == 0) {
                if ((cur.getX() <= point.getX()) && (last.getX() >= point.getX()) || (last.getX() <= point.getX()) && (cur.getX() >= point.getX()))
                    res = !res;
            } else {
                auto cross = (last.getX() - cur.getX()) * (point.getY() - cur.getY()) / deno + cur.getX();
                std::cout << cross << std::endl;

                if (cross <= point.getX())
                    res = !res;
            }
        }

        last = cur;
    }

    return res;
}

bool point_in_edge(EdgeCollider const& e, Vectorf const& point) {
    if (e.points.size() <= 1) {
        return e.points.size() == 0 ? false :
            point_in_circle({nullptr, e.points[0], e.radius}, point);
    }

    float d_min = -1;
    for (unsigned int pos = 1; pos < e.points.size(); ++pos) {
        if (d_min == -1)
            d_min = (getClosestPointInEdge(e.points[pos - 1], e.points[pos], point) - point).magnitude2();
        else
            d_min = min(d_min, (getClosestPointInEdge(e.points[pos - 1], e.points[pos], point) - point).magnitude2()); 
    }

    return d_min <= e.radius * e.radius;
}

Vectorf getClosestPointInEdge(Vectorf const& a, Vectorf const& b, Vectorf const& point) {
    auto seg = b - a;
    auto normal = seg.orthogonal();

    return Vectorf::lerpClamp(
        (a.getX() * normal.getY() - point.getX() * normal.getY() - normal.getX() * a.getY() + normal.getX() * point.getY()) / (seg.getY() * normal.getX() - seg.getX() * normal.getY())
        , a, b);
}

bool has_edge_intersection(Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d) {
    auto e0 = b - a;
    auto e1 = d - c;

    float deno = e0.getY() * e1.getX() - e0.getX() * e1.getY();
    float k = (a.getX() * e1.getY() - c.getX() * e1.getY() - e1.getX() * a.getY() + e1.getX() * c.getY()) / deno;
    float m = (e0.getX() * a.getY() - e0.getX() * c.getY() - a.getX() * e0.getY() + c.getX() * e0.getY()) / deno;

    return between_ii<float>(k, 0, 1) && between_ii<float>(m, 0, 1);
}

bool edge_intersection(Vectorf& result, Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d) {
    auto e0 = b - a;
    auto e1 = d - c;

    float deno = e0.getY() * e1.getX() - e0.getX() * e1.getY();

    if (deno == 0) {
        return false;
    }

    float m = (e0.getX() * a.getY() - e0.getX() * c.getY() - a.getX() * e0.getY() + c.getX() * e0.getY()) / deno;
    float k = (a.getX() * e1.getY() - c.getX() * e1.getY() - e1.getX() * a.getY() + e1.getX() * c.getY()) / deno;

    if (between_ii<float>(k, 0, 1) && between_ii<float>(m, 0, 1)) {
        result = a + e0 * m;
        return true;
    } else {
        return false;
    }
}

}

END_NAMESPACE_HAZ_GEOM2