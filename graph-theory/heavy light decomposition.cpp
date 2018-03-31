/*
* Description: heavy-light decomposition
* Demo: supports subtree/path/node updates, can also do same for queries
*       g[i][0] in hld contains heavy child of node i
* Dependencies: segment tree (implementation depends on update/queries required)
*/

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to;};
typedef vector <vector<edge>> graph;

struct heavyLightDecomposition
{
    int sz, timer = 0;
    bool edgeWeighted;
    graph g;
    vector <int> parent, sizes, root, position, endpos; //PS: endpos only for subtree query/update
    segmentTree st; //PS: can use other structures

    heavyLightDecomposition(graph &gr, bool e) //Remember that edgeWeighted means weights are in child
    {
        g = gr, sz = g.size(), edgeWeighted = e;
        st = segmentTree(sz);
        parent.resize(sz, -1), sizes.resize(sz, -1), root.resize(sz), position.resize(sz), endpos.resize(sz); //PS: see above
        reorder(), tour();
    }

    void reorder(int curr = 0)
    {
        sizes[curr] = 1;
        for (edge &e: g[curr]) if (e.to != parent[curr])
        {
            parent[e.to] = curr;
            reorder(e.to);
            sizes[curr] += sizes[e.to];
            if(sizes[e.to] > sizes[g[curr][0].to])
                swap(e, g[curr][0]);
        }
    }

    void tour(int curr = 0)
    {
        position[curr] = timer++;
        for (edge e: g[curr]) if (e.to != parent[curr])
        {
            root[e.to] = e.to == g[curr][0].to ? root[curr] : e.to;
            tour(e.to);
        }
        endpos[curr] = timer - 1; //PS: see above
    }

    template <class Operation>
    void process(int l, int r, Operation op)
    {
        for (; root[l] != root[r]; r = parent[root[r]])
        {
            if (position[root[l]] > position[root[r]]) swap(l, r);
            op(position[root[r]], position[r]);
        }
        if (edgeWeighted and l == r) return;
        if (position[l] > position[r]) swap(l, r);
        op(position[l] + edgeWeighted, position[r]); //Note: lca is l, if needed
    }

    void modifyNode(int p, int v) //PS: following functions optional
    {
        st.modify(position[p], v);
    }

    void modifyPath(int l, int r, int v)
    {
        process(l, r, [this, &v](int l, int r) {st.modify(l, r, v);});
    }

    void modifySubtree(int p, int v)
    {
        st.modify(position[p], endpos[p], v);
    }

    int queryPath(int l, int r)
    {
        int res = 0; //PS: max: -INF, min: INF, sum: 0
        process(l, r, [this, &res](int l, int r) {res += st.query(l, r);}); /*PS*/
        return res;
    }

    int querySubtree(int p)
    {
        return st.query(position[p], endpos[p]);
    }
};

int main()
{
    graph g;
    heavyLightDecomposition hld(g, false);

    return 0;
}
