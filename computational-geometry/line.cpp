/*
* Description: line/segment/ray operations (point incidence, distance, projection, reflection, intersection checks and calculations)
* Dependencies: pt class
*/

struct line
{
    pt a, b, ab;

    line(){}
    line(pt p, pt q) : a(p), b(q), ab(q - p) {}

    bool onLine(const pt &p) {return abs(ab ^ (p - a)) < EPS;}
    bool onRay(const pt &p)
    {
        if (!onLine(p)) return false;
        return ab * (p - a) >= 0;
    }
    bool onSegment(const pt &p) // PS: Change to > 0 and < ab.norm() if need strictly in segment
    {
        if (!onLine(p)) return false;
        ptT dot = ab * (p - a);
        return dot >= 0 and dot <= ab.norm2();
    }

    ptT distLine(const pt &p) {return abs((p - a) ^ ab) / sqrt(ab.norm2());}
    ptT distRay(const pt &p)
    {
        if ((p - a) * ab <= 0) return sqrt(p.dist2(a));
        return distLine(p);
    }
    ptT distSegment(const pt &p)
    {
        if ((p - a) * ab <= 0) return sqrt(p.dist2(a));
        if ((p - b) * ab >= 0) return sqrt(p.dist2(b));
        return distLine(p);
    }

    pt projection(const pt &p) {return a + ab * ((p - a) * ab) / ab.norm2();}
    pt reflection(const pt &p) {return 2 * projection(p) - p;}
    pt closestOnSegment(const pt &p)
    {
        if ((p - a) * ab <= 0) return a;
        if ((p - b) * ab >= 0) return b;
        return projection(p);
    }
};

bool intersectionSegment(const line &m, const line &n)
{
    if (orientation(m.a, m.b, n.a) == orientation(m.a, m.b, n.b)) return false;
    if (orientation(n.a, n.b, m.a) == orientation(n.a, n.b, m.b)) return false;
    return true;
}

pair <bool, pt> findIntersection(const line &m, const line &n, ii mtype, ii ntype) // pairs represent left/right endpoints, 0: no endpoint, 1: open endpoint, 2: closed endpoint
{
    auto endCheck = [](ptT v1, ptT v2, int type)
    {
        return type == 0 ? true : (type == 1 ? v1 < v2 : v1 <= v2);
    };
    ptT denom = m.ab ^ n.ab;
    if (abs(denom) < EPS) return {false, pt()}; // PS: assumes that parallel lines do not intersect
    ptT mt = (n.a - m.a) ^ n.ab;
    ptT nt = (n.a - m.a) ^ m.ab;
    if (denom < 0) denom = -denom, mt = -mt, nt = -nt;
    bool intersects = endCheck(0, mt, mtype.first) and endCheck(mt, denom, mtype.second) and
                      endCheck(0, nt, ntype.first) and endCheck(nt, denom, ntype.second);
    pt res = intersects ? m.a + m.ab * mt / denom : pt();
    return {intersects, res};
}
