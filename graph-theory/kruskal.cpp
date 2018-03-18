/*
* Description: kruskal's algorithm for minimum spanning tree
* Demo: returns cost of mst
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef int edgeT;

struct edge
{
    int i, j;
    edgeT d;
    bool operator < (const edge &o) const {return d < o.d;}
};

struct disjointSetUnion
{
    int sz;
    vector <int> par;

    disjointSetUnion(int s)
    {
        sz = s;
        par.resize(sz);
        for (int i = 0; i < sz; i++) par[i] = i;
    }

    int findRoot(int i)
    {
        return par[i] == i ? i : (par[i] = findRoot(par[i]));
    }

    void unionElements(int i, int j)
    {
        par[findRoot(i)] = findRoot(j);
    }

    bool sameComponent(int i, int j) {return findRoot(i) == findRoot(j);}
};

edgeT kruskal(vector <edge> &edges, int n)
{
    sort(edges.begin(), edges.end());
    disjointSetUnion dsu(n);
    edgeT cost = 0;
    int counter = 0;
    for (const edge &e: edges) if (!dsu.sameComponent(e.i, e.j))
    {
        dsu.unionElements(e.i, e.j);
        cost += e.d;
        if (++counter == n - 1) break;
    }
    return cost;
}

int main()
{
    int n = 8;
    vector <edge> edges = {{0, 1, 1}, {1, 2, 2}, {2, 3, 3}, {2, 4, 5}, {4, 3, 4}, {4, 5, 9},
                            {5, 6, 9}, {6, 7, 1}, {7, 5, 6}, {7, 4, 1}};

    //Expected: 18
    cout<<kruskal(edges, n)<<'\n';

    return 0;
}
