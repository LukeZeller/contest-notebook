/*
* Description: kosarju's algorithm for strongly connected components
* Demo: components stores the nodes in each SCC, category[i] is the component number for node i
*/

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

#define ll long long

struct edge{int to;};
typedef vector <vector<edge>> graph;

graph getTranspose(graph &g)
{
    graph t(g.size());
    for (int i = 0; i < g.size(); i++) for (edge e: g[i])
    {
        t[e.to].push_back({i});
    }
    return t;
}

struct kosarajuSCC
{
    int n, sz = 0; //sz is # of scc -> caution!! don't use components.size()
    graph g, t;
    vector <bool> visited; deque <int> ordered;
    vector <vector<int>> components; vector <int> category; /*PS*/

    kosarajuSCC(graph &gr)
    {
        g = gr, t = getTranspose(gr), n = g.size();
        visited.resize(n), components.resize(n), category.resize(n); /*PS*/
        getScc();
    }

    void getScc()
    {
        for (int i = 0; i < n; i++) if (!visited[i])
            ordering(i);
        for (int i: ordered) if (visited[i])
            categorize(i), ++sz;
    }

    void ordering(int curr)
    {
        if (visited[curr]) return;
        visited[curr] = true;
        for (edge e: g[curr]) if (!visited[e.to])
            ordering(e.to);
        ordered.push_front(curr);
    }

    void categorize(int curr)
    {
        if (!visited[curr]) return;
        visited[curr] = false;
        components[sz].push_back(curr), category[curr] = sz; /*PS*/
        for (edge e: t[curr]) if (visited[e.to])
            categorize(e.to);
    }
};

void addEdge(graph &g, int i, int j)
{
    g[i].push_back({j});
}

int main()
{
    int n = 5;
    graph g(n);

    addEdge(g, 2, 4), addEdge(g, 4, 0), addEdge(g, 0, 2);
    addEdge(g, 0, 3), addEdge(g, 3, 1), addEdge(g, 1, 3);

    auto scc = kosarajuSCC(g);

    /*Expected:
    * 0 2 4
    * 1 3
    */
    for (int i = 0; i < scc.sz; i++)
    {
        for (int j: scc.components[i]) cout<<j<<" ";
        cout<<'\n';
    }

    //Expected: 0 1 0 1 0
    for (int i = 0; i < n; i++) cout<<scc.category[i]<<" ";
    cout<<'\n';
}
