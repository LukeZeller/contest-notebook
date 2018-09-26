/*
* Description: convex hull trick for finding max/min
* Demo: static cht (queries only increasing) and dynamic cht (arbitrary queries) to find min using set of linear functions at given x-value
*/

struct equation
{
    ll a, b; // y = a * x + b

    ll y(ll x0){return a * x0 + b;}
    long double intersect(equation o){return (long double) (o.b - b) / (a - o.a);} //PS: this assumes two equations never have same slope, can just return INF if they do
};

// Requires monotone decreasing slope
// Use static getMin if monotone increasing x0, otherwise use dynamic getMin
// negate y() in equation to get maximum (monotone increasing slope needed for static)
struct convexHullTrick
{
    deque <equation> hull;

    void addEquation(const equation &e)
    {
        while (hull.size() > 1 and hull.rbegin()[1].intersect(e) < hull.rbegin()[1].intersect(hull.rbegin()[0]))
            hull.pop_back();
        hull.push_back(e);
    }

    ll getMinDynamic(ll x0)
    {
        if (hull.size() == 0)
            return 0; // PS: return value in case no functions exist

        int l = 0, r = hull.size() - 1;
        while (l < r)
        {
            int m = (l + r) / 2;
            if (hull[m].intersect(hull[m + 1]) >= x0)
                r = m;
            else
                l = m + 1;
        }
        return hull[l].y(x0);
    }

    ll getMinStatic(ll x0)
    {
        if (hull.empty()) return 0; //PS: same as above
        while (hull.size() > 1 and hull[0].y(x0) > hull[1].y(x0))
            hull.pop_front();
        return hull[0].y(x0);
    }
};

int main()
{
    convexHullTrick cht;
    cht.addEquation({3, 2}), cht.addEquation({1, 6}), cht.addEquation({0, 7});
    //Expected: (2 2) (5 5) (7 7) (7 7) (7 7)
    for (int i = 0; i < 5; i++) cout<<"("<<cht.getMinStatic(i)<<" "<<cht.getMinDynamic(i)<<") ";
    cout<<'\n';
}
