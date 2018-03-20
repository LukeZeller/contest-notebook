/*
* Description: closest pair of points (via line sweep)
* Demo: given vector of points returns pair of closest points
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

#define ll long long

typedef int ptsT; //PS: otherwise double
typedef ll ptlT; //PS: otherwise long double

const ll INF = 1e18;

struct pt
{
    ptsT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptlT operator * (const pt &o) const {return (ptlT) x * o.x + (ptlT) y * o.y;}

    ptlT norm2() const {return *this * *this;}
    ptlT dist2(const pt &o) const {return (*this - o).norm2();}
};

inline ptlT square(ptsT i) {return (ptlT) i * i;}

pair <pt, pt> closestPairPoints(vector <pt> &points)
{
    sort(points.begin(), points.end(), [](pt a, pt b){return make_pair(a.x, a.y) < make_pair(b.x, b.y);});
    set <pt> window = {points[0]};

    ptlT closest = INF;
    pair <pt, pt> res;
    for (int i = 1, left = 0; i < points.size(); i++)
    {
        while(i > left and square(points[i].x - points[left].x) > closest) window.erase(points[left++]);

        pt lb = {points[i].x, (ptsT) ceil(points[i].y - sqrt(closest))}; //PS: remove ceil if using doubles
        pt ub = {points[i].x, (ptsT) floor(points[i].y + sqrt(closest))}; //PS: remove floor if using doubles
        for (auto it = window.lower_bound(lb); it != window.upper_bound(ub); it++)
        {
            auto dist = it -> dist2(points[i]);
            if (dist < closest) closest = dist, res = {*it, points[i]};
        }
        window.insert(points[i]);
    }
    return res;
}

int main()
{
    vector <pt> points = {{0, 0}, {-4, 1}, {-7, -2}, {4, 5}, {1, 1}};

    auto sol = closestPairPoints(points);
    pt a = sol.first, b = sol.second;

    //Expected: 0 0 and 4 4 with distance: 1.414214
    cout<<a.x<<" "<<a.y<<" and "<<b.x<<" "<<b.y<<" with distance: "<<sqrt(a.dist2(b))<<'\n';

    vector <pt> points2 = {{0, 0}, {100, 45}, {2, 3}, {9, 9}, {0, 1}};
    sol = closestPairPoints(points2);
    a = sol.first, b = sol.second;

    //Expected: 0 0 and 0 1 with distance: 1.0
    cout<<a.x<<" "<<a.y<<" and "<<b.x<<" "<<b.y<<" with distance: "<<sqrt(a.dist2(b))<<'\n';

    return 0;
}
