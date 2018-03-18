/*
* Description: hierholzer's algorithm for euler path/circuit
* Demo: detects euler path/circuit for directed or undirected graph
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
    bool directed, isFeasible;
    vector <bool> used;
    deque <int> tour;

    eulerTour(graph &gr, bool dir)
    {
        g = gr, n = g.size(), directed = dir;
        if (directed and !feasibleDirected()) isFeasible = false; /*PS*/
        else if(!directed and !feasibleUndirected()) isFeasible = false; /*PS*/
        else
        {
            getEdge(), used.resize(m);
            dfs(root), isFeasible = tour.size() == m + 1;
        }
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++) m += g[i].size();
        if (!directed) m /= 2;
    }

    bool feasibleDirected() /*PS*/
    {
        vector <int> inDegree(n), outDegree(n);
        for (int i = 0; i < n; i++) for (edge e: g[i])
        {
            inDegree[e.to]++, outDegree[i]++;
        }
        int numLess = 0, numGreater = 0;
        for (int i = 0; i < n; i++)
        {
            if (!inDegree[i] and !outDegree[i]) continue;

            int diff = inDegree[i] - outDegree[i];
            if (diff > 1 or diff < -1) return false;
            if (diff < 0)
            {
                if (++numLess > 1) return false;
                root = i;
            }
            else if (diff > 0)
            {
                if (++numGreater > 1) return false;
            }
            else if(root == -1) root = i;
        }
        return numLess == numGreater;
    }

    bool feasibleUndirected() /*PS*/
    {
        vector <int> degree(n);
        for (int i = 0; i < n; i++)
        {
            degree[i] = g[i].size();
        }
        int numOdd = 0;
        for (int i = 0; i < n; i++)
        {
            if (!degree[i]) continue;

            bool odd = degree[i] & 1;
            if (odd)
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
void addEdge(graph &g, int i, int j, bool bi)
{
    g[i].push_back({j, currID});
    if (bi) g[j].push_back({i, currID});
    currID++;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    graph g(4);
    addEdge(g, 0, 1, false), addEdge(g, 0, 2, false), addEdge(g, 2, 3, false);
    auto etour = eulerTour(g, true);
    //Expected: 0
    cout<<etour.isFeasible<<'\n';

    g.clear(); g.resize(4);
    addEdge(g, 0, 1, false), addEdge(g, 0, 2, false), addEdge(g, 2, 3, false);
    addEdge(g, 3, 1, false), addEdge(g, 1, 0, false);
    etour = eulerTour(g, true);
    //Expected: 1
    cout<<etour.isFeasible<<'\n';

    g.clear(); g.resize(4);
    addEdge(g, 0, 1, true), addEdge(g, 0, 2, true), addEdge(g, 2, 3, true);
    addEdge(g, 3, 1, true), addEdge(g, 1, 0, true), addEdge(g, 2, 0, true);
    etour = eulerTour(g, false);
    //Expected: 1
    cout<<etour.isFeasible<<'\n';

    g.clear(); g.resize(5);
    addEdge(g, 0, 1, true), addEdge(g, 2, 3, true), addEdge(g, 2, 4, true);
    addEdge(g, 3, 1, true), addEdge(g, 1, 0, true), addEdge(g, 3, 2, true);
    etour = eulerTour(g, false);
    //Expected: 0
    cout<<etour.isFeasible<<'\n';

    return 0;
}
