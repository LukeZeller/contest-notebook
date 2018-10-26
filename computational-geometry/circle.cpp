/*
* Description: circle operations
* Demo: circle-circle intersection area, point inclusion
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

ld intersectionArea(circle a, circle b)
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
