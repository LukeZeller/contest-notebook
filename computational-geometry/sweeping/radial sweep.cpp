/*
* Description: radial sweep
* Demo: sortByAngleRay sorts points in order that ray extended from origin hits them (starts horizontal left, goes cw)
        sortByAngleLine sorts points in order than line from origin hits them (starts horizontal, goes cw)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

typedef ll ptT; //PS: otherwise long double
struct pt
{
    ptT x, y;
    bool rf; //PS: only for sorting by line

    bool operator == (const pt &o) const {return y == o.y and x == o.x;}
    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}

    pt reflect(const pt &o) const {return o + o - *this;}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    auto cp = (b - o) ^ (a - o);
    return cp > 0 ? 1 : (cp < 0 ? -1 : 0); //PS: change to > EPS and < -EPS for doubles
}

struct polarCmp //Caution !! need to make sure origin is not in list being sorted
{
    const pt o;

    polarCmp(const pt &origin) : o(origin) {}
    bool operator () (const pt &a, const pt &b) const
    {
        int orient = orientation(o, a, b);
        return orient == 1 or (orient == 0 and a < b);
    }
};

void sortByAngleRay(vector <pt> &points, const pt &origin)
{
    polarCmp cmp(origin);
    auto first = partition(points.begin(), points.end(), [&origin](const pt &p){return p == origin;});
    auto pivot = partition(first, points.end(), [&origin](const pt &p){return origin < p;});
    sort(points.begin(), pivot, cmp);
    sort(pivot, points.end(), cmp);
}

void sortByAngleLine(vector <pt> &points, const pt &origin)
{
    polarCmp cmp(origin);
    auto pivot = partition(points.begin(), points.end(), [&origin](const pt &p){return p.y == origin.y;});
    for (pt &p: points) if (p.y != origin.y)
    {
        if (p.y >= origin.y) p.rf = false;
        else p = p.reflect(origin), p.rf = true;
    }
    sort(pivot, points.end(), cmp);
    for (pt &p: points) if (p.y != origin.y and p.rf)
        p = p.reflect(origin);
}

int main()
{
    vector <pt> points = {{30, 30}, {60, 30}, {100, 20}, {70, 40}, {110, 40}, {40, 50}, {80, 70}};
    sortByAngleRay(points, {70, 40});

    //Expected: (70, 40), (40, 50), (80, 70), (110, 40), (100, 20), (60, 30), (30, 30)
    for (pt p: points) cout<<"("<<p.x<<", "<<p.y<<") ";
    cout<<'\n';

    sortByAngleLine(points, {70, 40});
    //Expected: (70, 40), (110, 40), (40, 50), (100, 20), (80, 70), (60, 30), (30, 30)
    for (pt p: points) cout<<"("<<p.x<<", "<<p.y<<") ";
    cout<<'\n';

    return 0;
}
