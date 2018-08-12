/*
* Description: convex polygon inclusion
* Demo: pointInTriangle returns if point is in/on/out of triangle
*        pointInConvexPolygon returns pair where first is in/on/out value and
*        triangle (poly[0], poly[second - 1], poly[second]) contains point
*/

int pointInTriangle(polygon &triangle, pt &p)
{
    int orient[3];
    for (int i = 0; i < 3; i++)
        orient[i] = orientation(triangle[i], triangle[next(i, 3)], p);
    if (orient[0] == orient[1] and orient[1] == orient[2]) return -1;
    for (int i = 0; i < 3; i++) if (orient[i] * orient[next(i, 3)] == -1) return 1;
    return 0;
} //inside: -1, outside: 1, on: 0

pair <int, int> pointInConvexPolygon(polygon &poly, pt &p)
{
    if (poly[0] == p) return {0, 2};
    if (poly.back() == p) return {0, poly.size() - 1};
    auto cmp = [&poly](pt a, pt b){return orientation(poly[0], a, b) == 1;};
    int pos = upper_bound(poly.begin() + 1, poly.end(), p, cmp) - poly.begin();
    if (pos == 1 or pos == poly.size()) return {1, pos};
    polygon triangle = {poly[pos - 1], poly[pos], poly[0]};
    return {pointInTriangle(triangle, p), pos};
} //inside: -1, outside: 1, on: 0
