/*
* Description: convex polygon algorithms
* Demo: andrew monotone chain, point inclusion (triangle, convex polygon), tangents to a point, shoelace formula, area of modified convex hull (add only), vertex rotation
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

typedef int ptsT; //PS: otherwise double
typedef ll ptlT; //PS: otherwise long double

const double EPS = 1e-9;

struct pt
{
    ptsT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptlT operator ^ (const pt &o) const {return (ptlT) x * o.y - (ptlT) y * o.x;}
    ptlT operator * (const pt &o) const {return (ptlT) x * o.x + (ptlT) y * o.y;}

    ptlT norm2() const {return *this * *this;}
    ptlT dist2(const pt &o) const {return (*this - o).norm2();}
};

int sgn(ptlT i) {return (i > -EPS) - (i < EPS);}
int orientation(pt &o, pt &a, pt &b) {return sgn((b - o) ^ (a - o));} //cw: 1, ccw: -1, col: 0

typedef vector<pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};

polygon andrewMonotoneChain(polygon &points, bool strict = true) //strict -> redundant points excluded
{
    sort(points.begin(), points.end());
    polygon hull; hull.reserve(points.size() + 1);
    for (int i = 0; i < 2; i++)
    {
        int s = hull.size();
        for (pt &p: points)
        {
            if (strict) while(hull.size() >= s + 2 and orientation(hull.rbegin()[1], hull.rbegin()[0], p) != 1)
                hull.pop_back();
            else while(hull.size() >= s + 2 and orientation(hull.rbegin()[1], hull.rbegin()[0], p) == -1)
                hull.pop_back();
            hull.push_back(p);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    if (hull.size() == 2 and hull[0] == hull[1]) hull.pop_back();
    return hull;
}

int pointInTriangle(polygon &triangle, pt &p) /*PS*/
{
    int orient[3];
    for (int i = 0; i < 3; i++)
        orient[i] = orientation(triangle[i], triangle[next(i, 3)], p);
    if (orient[0] == orient[1] and orient[1] == orient[2]) return -1;
    for (int i = 0; i < 3; i++) if (orient[i] * orient[next(i, 3)] == -1) return 1;
    return 0;
} //inside: -1, outside: 1, on: 0

pair <int, int> pointInConvexPolygon(polygon &poly, pt &point) //PS: requires pointInTriangle()
{
    auto cmp = [&poly](pt a, pt b){return orientation(poly[0], a, b) == 1;};
    int pos = upper_bound(poly.begin() + 1, poly.end(), point, cmp) - poly.begin();
    if (pos == 1 or pos == poly.size()) return {1, pos};
    polygon triangle = {poly[pos - 1], poly[pos], poly[0]};
    return {pointInTriangle(triangle, point), pos};
} //inside: -1, outside: 1, on: 0

vector <ptlT> getShoelaces(polygon &poly) /*PS*/
{
    int sz = poly.size();
    vector <ptlT> shoelace(sz + 1);
    for (int i = 0; i < sz; i++)
    {
        shoelace[i + 1] = shoelace[i] + (poly[i] ^ poly[next(i, sz)]); //Caution !! returns doubled/oriented area -> cw: negative
    }
    return shoelace;
}

ptlT polygonArea(polygon &poly){return getShoelaces(poly)[poly.size()];} /*PS*/

pair <int, int> findTangentsConvexPolygon(polygon &poly, pt p) //PS: requires pointInConvexPolygon
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

ptlT addPointConvexPolygonArea(polygon &poly, vector <ptlT> &shoelace, pt &p) //PS: requires findTangent()
{
    auto tangents = findTangentsConvexPolygon(poly, p);
    int lt = tangents.first, rt = tangents.second;
    if (lt == -1 and rt == -1) return shoelace[poly.size()];
    ptlT newArea = (poly[lt] ^ p) + (p ^ poly[rt]);
    if (lt < rt) return shoelace[lt] + (shoelace[poly.size()] - shoelace[rt]) + newArea;
    else return shoelace[lt] - shoelace[rt] + newArea;
}

polygon rotatePolygon(polygon &poly, int shift = 0) /*PS*/
{
    if (shift == 0) shift = min_element(poly.begin(), poly.end()) - poly.begin();
    polygon res(poly.size());
    for (int i = 0; i < poly.size(); i++)
    {
        res[i] = poly[(i + shift) % poly.size()];
    }
    return res;
}

polygon addPointConvexPolygon(polygon &poly, pt &p) //PS: requires findTangent(), rotatePolygon()
{
    auto tangents = findTangentsConvexPolygon(poly, p);
    int lt = tangents.first, rt = tangents.second;
    if (lt == -1 and rt == -1) return poly;
    polygon res;
    if (lt < rt)
    {
        res.push_back(p);
        for (int i = rt; i < poly.size(); i++) res.push_back(poly[i]);
        for (int i = 0; i <= lt; i++) res.push_back(poly[i]);
    }
    else
    {
        res.push_back(p);
        for (int i = rt; i <= lt; i++) res.push_back(poly[i]);
    }
    return rotatePolygon(res);
}

int main()
{
    polygon poly = {{10, 20}, {0, 0}, {10, 0}, {20, 10}, {0, 10}, {5, 5}};
    auto hull = andrewMonotoneChain(poly);
    auto shoelace = getShoelaces(hull);

    //Expected: (0, 0) (0, 10) (10, 20) (20, 10) (10, 0)
    for (pt p: hull) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';

    //Expected: 0 ... -500
    for (auto i: shoelace) cout<<i<<" "; cout<<'\n';

    vector <pt> add = {{20, 20}, {10, 10}, {-10, -10}, {-10, 10}, {55, -5}};
    /*Expected:
    * (0, 0) (0, 10) (10, 20) (20, 20) (20, 10) (10, 0)
    * -300 -300
    * (0, 0) (0, 10) (10, 20) (20, 10) (10, 0)
    * -250 -250
    * (-10, -10) (0, 10) (10, 20) (20, 10) (10, 0)
    * -350 -350
    * (0, 0) (-10, 10) (10, 20) (20, 10) (10, 0)
    * -350 -350
    * (55, -5) (0, 0) (0, 10) (10, 20)
    * -625 -625
    */
    for (int i = 0; i < add.size(); i++)
    {
        auto modified = addPointConvexPolygon(hull, add[i]);
        for (pt p: modified) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';
        cout<<addPointConvexPolygonArea(hull, shoelace, add[i]) / 2.0 <<" "<<polygonArea(modified) / 2.0<<'\n';
    }

    polygon rotated = rotatePolygon(hull, 3);
    //Expected: (20, 10) (10, 0) (0, 0) (0, 10) (10, 20)
    for (pt p: rotated) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';
    polygon original = rotatePolygon(rotated);
    //Expected: (0, 0) (0, 10) (10, 20) (20, 10) (10, 0)
    for (pt p: original) cout<<"("<<p.x<<", "<<p.y<<") "; cout<<'\n';

    return 0;
}
