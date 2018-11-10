/*
* Description: (max) online convex hull trick for general functions (if intersection can't be analytically found)
*              MAX_INTERSECTION must be set to highest x-coordinate at which two functions could intersection
*              intersection is binary searched upon, slope() returns "slope" between points near MAX_INTERSECTION
* Demo: dynamic cht (arbitrary queries and insertions) to find max using set of linear functions at given x-value
*/

bool chtQuery;
const ll MAX_INTERSECTION = 1e9; //PS: set value to a point where overtaking a function wouldn't matter anymore
struct equation
{
    mutable ll a, b;
    mutable long double intersectNxt = 0;

    ll y(ll x0) const {return a * x0 + b;}
    ll slope() const {return y(MAX_INTERSECTION) - y(MAX_INTERSECTION - 1);}

    ll intersect(equation o) const
    {
        ll l = -1, r = 1;
        bool atr = y(r) <= o.y(r);
        while (r < MAX_INTERSECTION and (y(r) <= o.y(r)) == atr)
            r *= 2;
        bool atl = y(l) <= o.y(l);
        while (l > -MAX_INTERSECTION and (y(l) <= o.y(l)) == atl)
            l *= 2;

        if (l <= -MAX_INTERSECTION and r >= MAX_INTERSECTION)
            return y(0) <= o.y(0) ? -INF : INF;

        atl = y(l) <= o.y(l);
        while (l < r)
        {
            auto m = l + (r - l) / 2;
            if ((y(m) <= o.y(m)) == atl)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }

    bool operator < (const equation &o) const
    {
        return chtQuery ? intersectNxt < o.intersectNxt : slope() < o.slope();
    }
};

struct convexHullTrick : multiset<equation>
{
    static const ll oo = numeric_limits<ll>::max() - 5;
    bool setNext(iterator x, iterator y)
    {
        if (y == end())
        {
            x -> intersectNxt = oo;
            return false;
        }
        else
            x -> intersectNxt = x -> intersect(*y);
        return x -> intersectNxt >= y -> intersectNxt;
    }

    void addEquation(equation e)
    {
        e.intersectNxt = 0;
        auto it = insert(e), nit = next(it);

        while (setNext(it, nit))
            nit = erase(nit);

        if (it == begin())
            return;

        auto pit = it;
        if (setNext(--pit, it))
            setNext(pit, it = erase(it));

        while (pit != begin())
        {
            it = pit;
            pit = prev(pit);
            if (it != begin() and pit -> intersectNxt >= it -> intersectNxt)
                setNext(pit, erase(it));
            else break;
        }
    }

    ll getMax(ll x0)
    {
        if (empty())
            return 0;

        chtQuery = true;
        auto l = *lower_bound({0, 0, x0});
        chtQuery = false;

        return l.y(x0);
    }
};
