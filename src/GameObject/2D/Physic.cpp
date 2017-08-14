#include <frameworkHaz/GameObject/2D/Physic.hpp>

BEG_NAMESPACE_HAZ_COLLISION

bool point_in_box(BoxCollider const& b, Vectorf const& point) {
    return haz::between_ii(point.x, b.left(), b.right()) 
        && haz::between_ii(point.y, b.top(), b.bottom());
}

bool point_in_circle(CircleCollider const& c, Vectorf const& point) {
    return (c.position() - point).magnitude2() <= c.radius * c.radius;
}

bool point_in_polygon(PolygonCollider const& p, Vectorf const& point) {
    const auto points = p.getPath();

    bool res = false;
    for (unsigned int pos = 0, prev = points.size() - 1; pos < points.size(); prev = pos++) {
        auto cur = points[pos];
        auto last = points[prev];

        if (((cur.y <= point.y) && (last.y >= point.y)) || ((last.y <= point.y) && (cur.y >= point.y))) {
            auto deno = last.y - cur.y;
            if (deno == 0) {
                return (((cur.x <= point.x) && (last.x >= point.x)) || ((last.x <= point.x) && (cur.x >= point.x)));
            } else {
                auto cross = (last.x - cur.x) * (point.y - cur.y) / deno + cur.x;

                if (cross == point.x)
                    return true;

                if (cross <= point.x) {
                    if (cross == cur.x && point.y == cur.y) {
                        if (cur.y > last.y)
                            res = !res;
                    } else if(cross == last.x && point.y == last.y) {
                        if (cur.y < last.y)
                            res = !res;
                    } else {
                        res = !res;
                    }
                }
            }
        }
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
        (a.x * normal.y - point.x * normal.y - normal.x * a.y + normal.x * point.y) / (seg.y * normal.x - seg.x * normal.y)
        , a, b);
}

bool has_edge_intersection(Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d) {
    auto e0 = b - a;
    auto e1 = d - c;

    float deno = e0.y * e1.x - e0.x * e1.y;
    float k = (a.x * e1.y - c.x * e1.y - e1.x * a.y + e1.x * c.y) / deno;
    float m = (e0.x * a.y - e0.x * c.y - a.x * e0.y + c.x * e0.y) / deno;

    return between_ii<float>(k, 0, 1) && between_ii<float>(m, 0, 1);
}

bool edge_intersection(Vectorf& result, Vectorf const& a, Vectorf const& b, Vectorf const& c, Vectorf const& d) {
    auto e0 = b - a;
    auto e1 = d - c;

    float deno = e0.y * e1.x - e0.x * e1.y;

    if (deno == 0) {
        return false;
    }

    float m = (e0.x * a.y - e0.x * c.y - a.x * e0.y + c.x * e0.y) / deno;
    float k = (a.x * e1.y - c.x * e1.y - e1.x * a.y + e1.x * c.y) / deno;

    if (between_ii<float>(k, 0, 1) && between_ii<float>(m, 0, 1)) {
        result = a + e0 * m;
        return true;
    } else {
        return false;
    }
}

END_NAMESPACE_HAZ_COLLISION

BEG_NAMESPACE_HAZ_HIDDEN

void _test_Collision_Polygon () {

    USING_NS_HAZ_2D
    USING_NS_HAZ_COLLISION

#define TEST_SQUARE(n, v...) WRITE(n " >>> " << (Vectorf v) << " : " << Collision::point_in_polygon(p, (Vectorf v)) << std::endl);

    PolygonCollider p(nullptr, {
        {25, 25}, {75, 25}, {75, 75}, {25, 75}
    });

    WRITE("   Y ^                           ");
    WRITE("     |                           ");
    WRITE(" 100 |          Y                ");
    WRITE("     |                           ");
    WRITE("  75 |     D----CD---C           ");
    WRITE("     |     |         |           ");
    WRITE("  50 |Z    DA   O    BC   X      ");
    WRITE("     |     |         |           ");
    WRITE("  25 |     A----AB---B           ");
    WRITE("     |                           ");
    WRITE("   0 |          W                ");
    WRITE("     -------------------------> X");
    WRITE("     0     25   50   75  100     " << std::endl);

    TEST_SQUARE("A (true)", {25, 25})
    TEST_SQUARE("B (true)", {75, 25})
    TEST_SQUARE("C (true)", {75, 75})
    TEST_SQUARE("D (true)", {75, 25})

    TEST_SQUARE("AB (true)", {50, 25})
    TEST_SQUARE("BC (true)", {75, 50})
    TEST_SQUARE("CD (true)", {50, 75})
    TEST_SQUARE("DA (true)", {25, 50})

    TEST_SQUARE("O (true)", {50, 50})

    TEST_SQUARE("W (false)", {50, 0})
    TEST_SQUARE("X (false)", {100, 50})
    TEST_SQUARE("Y (false)", {50, 100})
    TEST_SQUARE("Z (false)", {0, 50})

    p.setPath({
        {50, 0}, {100, 50}, {50, 100}, {0, 50}
    });
    std::cout << std::endl;

    WRITE("   Y ^                       ");
    WRITE("     |                       ");
    WRITE(" 100 |Z        D        Y    ");
    WRITE("     |      /    \\           ");
    WRITE("  75 |    DA       CD        ");
    WRITE("     |  /             \\      ");
    WRITE("  50 |A        O        C    ");
    WRITE("     |  \\             /      ");
    WRITE("  25 |    AB       BC        ");
    WRITE("     |      \\    /           ");
    WRITE("   0 |W        B        X    ");
    WRITE("     ---------------------> X");
    WRITE("     0    25   50  75  100   " << std::endl);

    TEST_SQUARE("A (true)", {0, 50})
    TEST_SQUARE("B (true)", {50, 0})
    TEST_SQUARE("C (true)", {100, 50})
    TEST_SQUARE("D (true)", {50, 100})

    TEST_SQUARE("AB (true)", {25, 25})
    TEST_SQUARE("BC (true)", {75, 25})
    TEST_SQUARE("CD (true)", {75, 75})
    TEST_SQUARE("DA (true)", {25, 75})

    TEST_SQUARE("O (true)", {50, 50})

    TEST_SQUARE("W (false)", {0, 0})
    TEST_SQUARE("X (false)", {100, 0})
    TEST_SQUARE("Y (false)", {100, 100})
    TEST_SQUARE("Z (false)", {0, 100})
}

END_NAMESPACE_HAZ_HIDDEN