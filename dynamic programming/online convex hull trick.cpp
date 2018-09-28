/*
* Description: online convex hull trick for finding min
* Demo: dynamic cht (arbitrary queries and insertions) to find min using set of linear functions at given x-value
*/

bool chtQuery;
struct equation
{
    mutable ll a, b; // y = a * x + b
    mutable long double intersectNxt = 0;

    ll slope() const {return a;}
    ll constant() const {return b;}
    ll y(ll x0) const {return a * x0 + b;}

    double intersect(equation o) const {return (long double) (o.b - b) / (a - o.a);}
    bool operator < (const equation &o) const // sort by slope if insert, sort by intersection if query
    {
        return chtQuery ? intersectNxt < o.intersectNxt : slope() > o.slope(); // PS: change to slope() < o.slope() for max queries
    }
};

struct convexHullTrick : multiset<equation>
{
    const ll oo = numeric_limits<ll>::max() - 5;
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
        auto it = insert(e);
        if (setNext(it, next(it)))
        {
            erase(it);
            return;
        }
        if (it == begin())
            return;

        setNext(prev(it), it);

        auto pit = prev(it);
        while (pit != begin())
        {
            it = pit, pit = prev(pit);
            if (pit -> intersectNxt >= it -> intersectNxt)
                setNext(pit, erase(it));
            else
                break;
        }
    }

    ll getMin(ll x0)
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
    cht.addEquation({3, 2}), cht.addEquation({1, 6}), cht.addEquation({0, 7});
    //Expected: 2 5 7 7 7
    for (int i = 0; i < 5; i++) cout<<cht.getMin(i)<<" ";
    cout<<'\n';
}
