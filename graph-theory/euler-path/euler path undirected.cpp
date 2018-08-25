/*
* Description: hierholzer's algorithm for euler path
* Demo: detects euler path for undirected graph
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
        if(isFeasible = feasible())
        {
            getEdge(), used.resize(m);
            dfs(root), isFeasible = tour.size() == m + 1;
        }
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++)
            m += g[i].size();
        m /= 2;
    }

    bool feasible()
    {
        int numOdd = 0;
        for (int i = 0; i < n; i++) if (g[i].size())
        {
            if (g[i].size() & 1)
            {
                if (++numOdd > 2) return false;
                root = i;
            }
            else if(root == -1) root = i;
        }
        return numOdd == 0 or numOdd == 2;
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
    g[j].push_back({i, currID});
    currID++;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    graph g(4);
    addEdge(g, 0, 1), addEdge(g, 0, 2), addEdge(g, 2, 3);
    addEdge(g, 3, 1), addEdge(g, 1, 0), addEdge(g, 2, 0);
    auto etour = eulerTour(g);
    //Expected: 1
    cout<<etour.isFeasible<<'\n';

    g.clear(); g.resize(5);
    addEdge(g, 0, 1), addEdge(g, 2, 3), addEdge(g, 2, 4);
    addEdge(g, 3, 1), addEdge(g, 1, 0), addEdge(g, 3, 2);
    etour = eulerTour(g);
    //Expected: 0
    cout<<etour.isFeasible<<'\n';

    return 0;
}
