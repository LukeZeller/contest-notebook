/*
* Description: binary lifting to find lowest common ancestor
*/

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to;};
typedef vector<vector<edge>> graph;

struct binaryLift
{
    int sz, h;
    graph g;
    vector <vector<int>> table;
    vector <int> depths;

    binaryLift(graph &gr)
    {
        g = gr, sz = g.size(), h = 0, calcHeight();
        table.resize(sz, vector<int>(h, -1)), depths.resize(sz);
        build(0);
    }

    void calcHeight(){while (1 << h < sz) h++;}

    void build(int curr, int depth = 0)
    {
        depths[curr] = depth;
        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
        }
        for (edge e: g[curr]) if (e.to != table[curr][0])
        {
            table[e.to][0] = curr;
            build(e.to, depth + 1);
        }
    }

    int lca(int l, int r)
    {
        if (depths[l] > depths[r]) swap(l, r);
        for (int i = h - 1; i >= 0; i--)
        {
            if ((1 << i) & (depths[r] - depths[l]))
                r = table[r][i];
        }
        if (l == r) return l;
        for (int i = h - 1; i >= 0; i--) if (table[l][i] != table[r][i])
        {
            l = table[l][i], r = table[r][i];
        }
        return table[l][0];
    }
};

void addEdge(graph &g, int i, int j)
{
    g[i].push_back({j});
    g[j].push_back({i});
}

int main()
{
    int n = 5;
    graph g(n);
    addEdge(g, 0, 1), addEdge(g, 0, 2), addEdge(g, 1, 3), addEdge(g, 1, 4);

    auto bl = binaryLift(g);
    //Expected: 0 1 0 1
    cout<<bl.lca(0, 0)<<" "<<bl.lca(3, 4)<<" "<<bl.lca(3, 2)<<" "<<bl.lca(4, 1)<<'\n';

    return 0;
}
