/*
* Description: online convex hull trick for finding min
* Demo: dynamic cht (arbitrary queries and insertions) to find min using set of linear functions at given x-value
*/

struct equation
{
    ll a, b; // y = a * x + b

    ll y(ll x0) const {return a * x0 + b;}
    long double intersect(equation o) const {return (long double) (o.b - b) / (a - o.a);} // PS: this assumes two equations never have same slope, can just return INF if they do

    bool operator < (const equation &o) const // PS: sort by slope (faster growing equation comes first)
    {
        return a > o.a;
    }
};

// negate y() and both sides of slope comparator in equation to get maximum
struct convexHullTrick
{
    vector <vector <equation>> hulls;

    void addEquation(const equation &e)
    {
        vector <equation> carry = {e};
        for (int i = 0; ; i++)
        {
            if (i >= hulls.size())
                hulls.emplace_back();

            if (hulls[i].empty())
            {
                hulls[i] = move(carry);
                break;
            }
            else
                mergeHulls(carry, hulls[i]);
        }
    }

    ll getMin(ll x0)
    {
        bool nonEmpty = false;
        ll res = INF;
        for (const auto &hull: hulls) if (!hull.empty())
            res = min(res, getMinDynamic(hull, x0)), nonEmpty = true;
        return nonEmpty ? res : 0; // PS: return value if there are no equations (currently returns 0)
    }

    ll getMinDynamic(const vector <equation> &hull, ll x0)
    {
        if (hull.empty())
            return numeric_limits<ll>::max();

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

    static void mergeHulls(vector <equation> &a, vector <equation> &b) // a = a union b, b = empty after call
    {
        a.insert(a.end(), b.begin(), b.end());
        sort(a.begin(), a.end());

        deque <equation> temp;
        for (equation e: a)
        {
            while (temp.size() > 1 and temp.rbegin()[1].intersect(e) < temp.rbegin()[1].intersect(temp.rbegin()[0]))
                temp.pop_back();
            temp.push_back(e);
        }
        a.clear(), b.clear();
        a.insert(a.end(), temp.begin(), temp.end());
    }
};

int main()
{
    convexHullTrick cht;
    cht.addEquation({3, 2}), cht.addEquation({1, 6}), cht.addEquation({0, 7});
    //Expected: 2 5 7 7 7
    for (int i = 0; i < 5; i++) cout<<cht.getMin(i)<<" ";
    cout<<'\n';
}
