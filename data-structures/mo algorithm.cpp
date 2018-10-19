/*
* Description: Mo's algorithm for solving subarray queries on static array in O(n sqrt n) time
* Demo: Querying the # of unique elements in [l, r] range
*/

const int BLOCK = 447; /*PS*/

struct mo_query
{
    int l, r, ind;

    bool operator < (mo_query o) const
    {
        if (l / BLOCK != o.l / BLOCK)
            return l < o.l;
        else
            return (l / BLOCK) & 1 ? (o.r < r) : (r < o.r);
    }
};

int counts[1000]; // PS: Information needed to update sol
void mo_add(int elem, int &sol) // update sol after elem is added
{
    sol += (++counts[elem] == 1);
}

void mo_rmv(int elem, int &sol) // update sol after elem is removed;
{
    sol -= (--counts[elem] == 0);
}

vector <int> mo_solve(vector <mo_query> &queries, vector <int> &a) // a is static vector used to answer queries
{
    int sol = 0; // PS: (Initial) Solution for blank subarray
    int lp = 0, rp = 0;
    vector <int> sols(queries.size());
    sort(queries.begin(), queries.end());
    for (auto q: queries)
    {
        while (lp < q.l)
            mo_rmv(a[lp++], sol);
        while (lp > q.l)
            mo_add(a[--lp], sol);
        while (rp <= q.r)
            mo_add(a[rp++], sol);
        while (rp - 1 > q.r)
            mo_rmv(a[--rp], sol);

        sols[q.ind] = sol;
    }
    return sols;
}

int main()
{
    vector <int> a = {7, 3, 2, 2, 3, 1};
    int n = a.size();
    vector <mo_query> queries(n);
    for (int i = 0; i < n; i++)
    {
        queries[i] = {i, n - 1}; // i-th query is on [i, n - 1] interval
        queries[i].ind = i;
    }
    // Expected: 4 3 3 3 2 1
    for (auto sol: mo_solve(queries, a))
        cout << sol << " ";
    cout << '\n';
}
