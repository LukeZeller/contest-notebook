/*
* Description: toposort using bfs
* Demo: returns toposorted vertices and whether graph has cycle, unique ordering, or multiple orderings
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge{int to;};
typedef vector <vector<edge>> graph;

pair <int, vector <int>> toposort(graph &g) //PS: modify return type as needed
{
    int n = g.size();
    queue <int> q;
    vector <int> inDegree(n), sorted;

    for (int i = 0; i < n; i++) for (edge e: g[i])
        inDegree[e.to]++;
    for (int i = 0; i < n; i++) if (inDegree[i] == 0)
        q.push(i);

    bool hasBranch = false; /*PS*/
    while (!q.empty())
    {
        if (q.size() > 1) hasBranch = true; /*PS*/
        int curr = q.front();
        q.pop();
        sorted.push_back(curr);

        for (edge e: g[curr]) if (--inDegree[e.to] == 0)
            q.push(e.to);
    }
    if (sorted.size() < n) return make_pair(0, sorted); //graph has cycle
    else return hasBranch ? make_pair(2, sorted) : make_pair(1, sorted); /*PS*/
}

void addEdge(graph &g, int i, int j)
{
    g[i].push_back({j});
}

int main()
{
    graph g1(4);
    addEdge(g1, 2, 0), addEdge(g1, 0, 1), addEdge(g1, 1, 3);
    auto res1 = toposort(g1);

    //Expected: 1
    cout<<res1.first<<'\n';

    //Expected: 2 0 1 3
    for (int i: res1.second) cout<<i<<" ";
    cout<<'\n';

    graph g2(5);
    addEdge(g2, 0, 2), addEdge(g2, 2, 3), addEdge(g2, 2, 1), addEdge(g2, 3, 0), addEdge(g2, 4, 0);
    auto res2 = toposort(g2);

    //Expected: 0
    cout<<res2.first<<'\n';

    //Expected: 4 (doesn't matter)
    for (int i: res2.second) cout<<i<<" ";
    cout<<'\n';

    graph g3(5);
    addEdge(g3, 4, 3), addEdge(g3, 4, 2), addEdge(g3, 3, 0), addEdge(g3, 2, 1);
    auto res3 = toposort(g3);

    //Expected: 2
    cout<<res3.first<<'\n';

    //Expected partition: 4 | 2 3 | 0 1
    for (int i: res3.second) cout<<i<<" ";
    cout<<'\n';

    return 0;
}
