/*
* Description: online convex hull trick for finding max
* Demo: dynamic cht (arbitrary queries and insertions) to find max using set of linear functions at given x-value
*/

bool chtQuery;
struct equation
{
    mutable ll a, b; // PS: y = a * x + b
    mutable long double intersectNxt = 0;

    ll slope() const {return a;} /*PS*/
    ll constant() const {return b;} /*PS*/
    ll y(ll x0) const {return a * x0 + b;} /*PS*/
    ld intersect(equation o) const {return ld (o.b - b) / (a - o.a);} /*PS*/

    bool operator < (const equation &o) const // sort by slope if insert, sort by intersection if query
    {
        return chtQuery ? intersectNxt < o.intersectNxt : slope() < o.slope();
    }
};

// PS: Negate coefficients of equations to get min queries
struct convexHullTrick : multiset<equation>
{
    static const ll oo = numeric_limits<ll>::max() - 5;
    bool setNext(iterator x, iterator y) // returns true if x makes y redundant
    {
        if (y == end())
        {
            x -> intersectNxt = oo;
            return false;
        }
        if (x -> slope() == y -> slope())
            x -> intersectNxt = x -> constant() > y -> constant() ? oo : -oo;
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
            return 0; // PS: return value if there are no equations

        chtQuery = true;
        auto l = *lower_bound({0, 0, x0});
        chtQuery = false;

        return l.y(x0);
    }
};

int main()
{
    convexHullTrick cht;
    cht.addEquation({-3, -2}), cht.addEquation({-1, -6}), cht.addEquation({-0, -7});
    //Expected: 2 5 7 7 7
    for (int i = 0; i < 5; i++) cout<<-cht.getMax(i)<<" ";
    cout<<'\n';
}
