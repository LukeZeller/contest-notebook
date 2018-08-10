/*
* Description: finding tangents of convex polygon
* Demo: findTangentsConvexPoly returns pair of indices of tangent points (returns (-1, -1) if point is on/in polygon)
        addPointConvexPolygonArea returns the area of the polygon after point p is inserted (requires shoelaces to be passed in)
* Dependency: convex polygon inclusion
*/

pair <int, int> findTangentsConvexPolygon(polygon &poly, pt p)
{
    int sz = poly.size();
    auto res = pointInConvexPolygon(poly, p);
    if (res.first != 1) return {-1, -1};
    int rp = res.second, lp = prev(res.second, sz);

    int l = 0, r = sz - 1;
    while (l < r)
    {
        int m = (l + r + 1) / 2;
        pt curr = poly[prev(lp, sz, m)];
        pt nxt = poly[next(prev(lp, sz, m), sz)];
        if (orientation(p, curr, nxt) != 1 and orientation(poly[0], curr, p) != -1) l = m;
        else r = m - 1;
    }
    int leftTangent = prev(lp, sz, l);

    l = 0, r = sz - 1;
    while (l < r)
    {
        int m = (l + r + 1) / 2;
        pt curr = poly[next(rp, sz, m)];
        pt nxt = poly[prev(next(rp, sz, m), sz)];
        if (orientation(p, curr, nxt) != -1 and orientation(poly[0], curr, p) != 1) l = m;
        else r = m - 1;
    }
    int rightTangent = next(rp, sz, l);

    return {leftTangent, rightTangent};
}

ptT addPointConvexPolygonArea(polygon &poly, vector <ptT> &shoelace, pt &p)
{
    auto tangents = findTangentsConvexPolygon(poly, p);
    int lt = tangents.first, rt = tangents.second;
    if (lt == -1 and rt == -1) return shoelace[poly.size()];
    ptT newArea = (poly[lt] ^ p) + (p ^ poly[rt]);
    if (lt < rt) return shoelace[lt] + (shoelace[poly.size()] - shoelace[rt]) + newArea;
    else return shoelace[lt] - shoelace[rt] + newArea;
}

int main()
{
    polygon poly = {{0, 0}, {0, 10}, {10, 20}, {20, 10}, {10, 0}};
    auto shoelace = getShoelaces(poly);

    vector <pt> add = {{20, 20}, {10, 10}, {-10, -10}, {-10, 10}, {55, -5}};
    // Expected: 300 250 350 350 625
    for (int i = 0; i < add.size(); i++)
    {
        cout<<abs(addPointConvexPolygonArea(poly, shoelace, add[i]) / 2.0)<<'\n';
    }

    return 0;
}
