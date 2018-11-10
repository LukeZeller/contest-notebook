/*
* Description: circle operations
* Demo: circle-circle intersection area, point inclusion, circle-circle inclusion, line-circle intersection, 
        circle-circle tangents, trimming vector of circles
* Dependencies: trigonometry functions (angle_LOC, area_SAS), line class (distLine)
              pt class (+, *, /, -, * product, norm2(), dist2(), normalize(), rotateCw, perpCw)
*/

const ld PI = 3.14159265358979323846; // or acos(-1)

struct circle
{
    pt center; ptT r;
    ld area() const {return PI * r * r;}
};

int pointInCircle(circle &c, const pt &p)
{
    auto d = sqrt(c.center.dist2(p));
    return d > c.r + EPS ? 1 : (d < c.r - EPS ? -1 : 0);
} // inside: -1, outside: 1, on: 0

int circleInCircle(const circle &a, const circle &b)
{
    auto dr = a.r - b.r;
    if (a.center.dist2(b.center) <= dr * dr + EPS)
        return dr < -EPS ? 1 : (dr > EPS ? -1 : 0);
    else
        return 1;
} // -1: a strictly contains b, 0: a equal to b, 1: a does not contain b

int lineIntersectsCircle(const line &l, const circle &c)
{
    auto diff = l.distLine(c.center) - c.r;
    return diff <= -EPS ? -1 : (diff >= EPS ? 1 : 0);
} // -1 : intersects at 2 points, 0 : intersects at 1 point, 1 : no intersection

vector <pt> findLineCircleIntersection(const line &l, const circle &c)
{
    vector <pt> intersections;
    ld d = l.distLine(c.center), h2 = c.r * c.r - d * d;
    if (h2 > -EPS)
    {
        h2 = max(ld(0), h2);
        pt p = l.projection(c.center);
        pt h = l.ab * sqrt(h2) / sqrt(l.ab.norm2());
        intersections = {p - h, p + h};
        if (h2 < EPS)
            intersections.pop_back();
    }
    return intersections;
}

ld circleCircleIntersectionArea(circle a, circle b)
{
    auto c1 = a.center, c2 = b.center;
    auto r1 = a.r, r2 = b.r, d = sqrt(c1.dist2(c2));
    if (c1.dist2(c2) + EPS >= (r1 + r2) * (r1 + r2))
        return 0;
    if (c1.dist2(c2) <= (r2 - r1) * (r2 - r1) + EPS)
        return PI * min(r1, r2) * min(r1, r2);
    auto alpha = 2 * angle_LOC(r1, d, r2);
    auto beta = 2 * angle_LOC(r2, d, r1);
    auto res = alpha * r1 * r1 / 2.0 - area_SAS(r1, r1, alpha)
             + beta * r2 * r2 / 2.0 - area_SAS(r2, r2, beta);
    return res;
}

pair <ld, vector<pt>> findCircleCircleIntersection(const circle &a, const circle &b) // intersections are from left to right wrt a's center, ie. orient(a.center, p[0], p[1]) = 1
{
    vector <pt> intersections;
    auto c1 = a.center, c2 = b.center;
    auto r1 = a.r, r2 = b.r, d = sqrt(c1.dist2(c2));
    if (c1.dist2(c2) + EPS >= (r1 + r2) * (r1 + r2))
        return {0, {}};
    if (c1.dist2(c2) <= (r2 - r1) * (r2 - r1) + EPS)
        return {PI * min(r1, r2) * min(r1, r2), {}}; // PS: don't return intersection points if concentric
    auto alpha = angle_LOC(r1, d, r2);
    auto beta = angle_LOC(r2, d, r1);
    auto v = (c2 - c1) * r1 / d;
    intersections = {c1 + v.rotateCcw(alpha), c1 + v.rotateCw(alpha)};
    if (intersections[0] == intersections[1])
        intersections.pop_back();
    alpha *= 2, beta *= 2;
    auto res = alpha * r1 * r1 / 2.0 - area_SAS(r1, r1, alpha)
             + beta * r2 * r2 / 2.0 - area_SAS(r2, r2, beta);
    return {res, intersections};
}

vector <line> findTangents(circle a, circle b, bool exterior) // each tangent's direction will be from a to b (unless it's a single vertial tangent, then it'll be arbitrary)
{
    vector <line> res;
    if (!exterior) b.r *= -1;

    pt ab = b.center - a.center;
    auto dr = a.r - b.r, d2 = ab.norm2(), h2 = d2 - dr * dr;
    if (abs(d2) < EPS or h2 < 0)
        return res; // PS: return value (currently empty) when one circle is contained in the other

    for (auto sign : {-1, 1})
    {
        ld alpha = atan2(sqrt(h2), dr);
        pt v = ab.rotateCw(sign * alpha) / sqrt(d2);
        res.push_back({a.center + v * a.r, b.center + v * b.r});
        if (abs(h2) < EPS)
        {
            auto tangent = res.back().a;
            return {{tangent - v.perpCw(), tangent + v.perpCw()}}; // PS: If tangent at one point, return tangent line of arbitrary length
        }
    }
    return res;
}

vector <circle> trimOverlap(const vector <circle> &circles) // removes circles that are entirely contained within another circle, if multiple circles are identical, only 1 copy is kept
{
    int n = circles.size();
    vector <circle> res;
    vector <int> redundant(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) if (i != j)
        {
            auto inclusion = circleInCircle(circles[i], circles[j]);
            if (inclusion == -1)
                redundant[j] = true;
            else if (inclusion == 0)
                redundant[max(i, j)] = true;
        }
    }
    for (int i = 0; i < n; i++) if (!redundant[i])
        res.push_back(circles[i]);
    return res;
}
