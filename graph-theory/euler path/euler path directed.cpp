/*
* Description: hierholzer's algorithm for euler path
* Demo: detects euler path for directed graph
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

struct eulerTour
{
    int n, m = 0, root = -1;
    graph g;
    bool isFeasible;
    vector <bool> used;
    deque <int> tour;

    eulerTour(graph &gr)
    {
        g = gr, n = g.size();
        if (isFeasible = feasible())
        {
            getEdge(), used.resize(m);
            dfs(root), isFeasible = tour.size() == m + 1;
        }
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++)
            m += g[i].size();
    }

    bool feasible()
    {
        vector <int> in(n), out(n);
        for (int i = 0; i < n; i++) for (edge e: g[i])
            in[e.to]++, out[i]++;
        int neg = 0, pos = 0;
        for (int i = 0; i < n; i++)
        {
            if (!in[i] and !out[i]) continue;

            int diff = in[i] - out[i];
            if (abs(diff) > 1) return false;
            if (diff < 0)
            {
                if (++neg > 1) return false;
                root = i;
            }
            else if (diff > 0)
            {
                if (++pos > 1) return false;
            }
            else if(root == -1) root = i;
        }
        return neg == pos;
    }

    void dfs(int curr)
    {
        for (edge e: g[curr]) if (!used[e.id])
        {
            used[e.id] = true;
            dfs(e.to);
        }
        tour.push_front(curr);
    }
};

int currID = 0;
void addEdge(graph &g, int i, int j)
{
    g[i].push_back({j, currID});
    currID++;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    graph g(4);
    addEdge(g, 0, 1), addEdge(g, 0, 2), addEdge(g, 2, 3);
    auto etour = eulerTour(g);
    //Expected: 0
    cout<<etour.isFeasible<<'\n';

    g.clear(); g.resize(4);
    addEdge(g, 0, 1), addEdge(g, 0, 2), addEdge(g, 2, 3);
    addEdge(g, 3, 1), addEdge(g, 1, 0);
    etour = eulerTour(g);
    //Expected: 1
    cout<<etour.isFeasible<<'\n';

    return 0;
}
