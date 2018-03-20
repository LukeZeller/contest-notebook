/*
* Description: convex hull trick for finding max/min
* Demo: static cht (queries only increasing) to find min using set of linear functions
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define ll long long

struct equation
{
    ll m, b;

    ll y(ll x0){return m * x0 + b;} //PS: different for quadtratic
    double intersect(equation o){return double(o.b - b) / (m - o.m);} //PS: same as above
};

struct convexHullTrick
{
    deque <equation> hull;

    void addEquation(const equation &e) //PS: negate values in equation to get maximum
    {
        while (hull.size() > 1 and hull.rbegin()[1].intersect(e) < hull.rbegin()[1].intersect(hull.rbegin()[0]))
            hull.pop_back();
        hull.push_back(e);
    }

    ll getValue(ll x0)
    {
        if (hull.empty()) return 0;
        while (hull.size() > 1 and hull[0].y(x0) > hull[1].y(x0))
            hull.pop_front();
        return hull[0].y(x0); //PS: negate result if negated equations
    }
};

int main()
{
    convexHullTrick cht;
    cht.addEquation({3, 2}), cht.addEquation({1, 6}), cht.addEquation({0, 7});
    //Expected: 2 5 7 7 7
    for (int i = 0; i < 5; i++) cout<<cht.getValue(i)<<" ";
    cout<<'\n';

    return 0;
}
