/*
* Description: disjoint set union on rooted trees (use if you can calculate all needed information for a node after processing its subtree)
* Demo: finds # of odd-indexed nodes in each node's subtree
*/

struct dsuOnTree
{
    graph g;
    int sz, timer = 0;
    vector <int> in, out, ordered, sizes;

    vector <int> sols;
    int numOdd = 0; //PS: replace w/ problem specific parameters

    dsuOnTree(graph &gr) : g(gr), sz(g.size()), in(sz), out(sz), ordered(sz), sizes(sz), sols(sz)
    {
        tour(), dfs();
    }

    int tour(int curr = 0, int prev = -1)
    {
        sizes[curr] = 1;
        ordered[timer] = curr, in[curr] = timer++;
        for (edge e: g[curr]) if (e.to != prev)
            sizes[curr] += tour(e.to, curr);
        out[curr] = timer;
        return sizes[curr];
    }

    void add(int i) //PS: modify PS parameters for when node v is updated
    {
        numOdd += i & 1;
    }

    void rmv(int i) //PS: modify PS parameters for when node v is removed
    {
        numOdd -= i & 1;
    }

    void dfs(int curr = 0, int prev = -1, bool keep = false)
    {
        int mx = -1, heavy = -1;
        for (edge e: g[curr]) if (e.to != prev and sizes[e.to] > mx)
            mx = sizes[e.to], heavy = e.to;
        for (edge e: g[curr]) if (e.to != prev and e.to != heavy)
            dfs(e.to, curr);
        if (heavy != -1)
            dfs(heavy, curr, true);
        for (edge e: g[curr]) if (e.to != prev and e.to != heavy)
            for (int t = in[e.to]; t < out[e.to]; t++)
                add(ordered[t]);
        add(curr);
        sols[curr] = numOdd; //PS: set solution for curr node using PS parameters
        if (keep) return;
        for (int t = in[curr]; t < out[curr]; t++)
            rmv(ordered[t]);
    }
};

int main()
{
    graph g(5);
    g[0] = {{1}, {2}}, g[1] = {{0}}, g[2] = {{0}, {3}, {4}}, g[3] = {{2}}, g[4] = {{2}};
    dsuOnTree dsu(g);
    // Expected: 2 1 1 1 0
    for (auto i: dsu.sols)
        cout << i << " ";
    cout<<'\n';
}
