/*
* Description: label setting algorithm for longest path on DAG
* Demo: return vector of distances from single source (can be modified to find global longest path)
* Modification: find global longest path by replacing q.push(s) by placing all 0-inDegree nodes in queue
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ll long long

const ll INF = 1e18;

struct edge{int to, w;};
typedef vector<vector<edge>> graph;

vector <ll> labelSettingLongest(graph &g, int s) //PS: negate edges for shortest path
{
    int n = g.size();
    queue <int> q;
    vector <int> inDegree(n);
    vector <ll> distances(n, -INF);

    for (int i = 0; i < n; i++) for (edge e: g[i])
        inDegree[e.to]++;

    q.push(s);
    distances[s] = 0;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        for (edge e: g[curr])
        {
            distances[e.to] = max(distances[e.to], distances[curr] + e.w); //PS: replace w/ dist[curr] - e.w for shortest
            if(--inDegree[e.to] == 0) q.push(e.to);
        }
    }
    return distances; //PS: negate all values if finding shortest
}

void addEdge(graph &g, int i, int j, int w)
{
    g[i].push_back({j, w});
}

int main()
{
    graph g(7);

    addEdge(g, 0, 1, 5), addEdge(g, 1, 2, 6), addEdge(g, 1, 3, 1);
    addEdge(g, 3, 5, -4), addEdge(g, 5, 6, 9), addEdge(g, 3, 4, 10);
    addEdge(g, 2, 4, 2), addEdge(g, 4, 5, -12), addEdge(g, 4, 6, 1);

    //Expected: N/A 0 6 1 11 -1 12
    for (auto dist: labelSettingLongest(g, 1))
    {
        if (dist == -INF) cout<<"N/A"<<" ";
        else cout<<dist<<" ";
    }
    cout<<'\n';

    return 0;
}
