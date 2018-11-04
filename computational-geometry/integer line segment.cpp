/*
* Description: line segments w/ integer endpoints class
* Demo: numIntegerPoints() find the # of integer coordinate points on a integer_line
*       integerIntersection() returns (intersects, pt) pair: intersects is true iff m, n intersect at int-coordinate point (stored in pt)
* Dependencies: gcd for num points, pt class (+, -, ^) for intersection
*/

struct integer_line
{
    pt a, b, ab; // Caution !! Make sure ptT is long long and not double/long double

    integer_line(){}
    integer_line(pt p, pt q) : a(p), b(q), ab(q - p) {}

    int numIntegerPoints(bool exclude = false) const
    {
        return gcd(abs(a.x - b.x), abs(a.y - b.y)) + (exclude ? -1 : 1);
    }
};

pair <bool, pt> integerIntersection(const integer_line &m, const integer_line &n)
{
    ptT denom = m.ab ^ n.ab;
    if (denom == 0) return {false, pt()}; // PS: assumes that parallel lines do not intersect
    ptT mt = (n.a - m.a) ^ n.ab;
    ptT nt = (n.a - m.a) ^ m.ab;
    if (denom < 0) denom = -denom, mt = -mt, nt = -nt;
    bool intersects = 0 <= mt and mt <= denom and 0 <= nt and nt <= denom;
    bool atInteger = (m.ab.x * mt % denom == 0) and (m.ab.y * mt % denom == 0);
    pt res = (intersects and atInteger) ? m.a + pt{m.ab.x * mt / denom, m.ab.y * mt / denom} : pt();
    return {intersects and atInteger, res};
}
