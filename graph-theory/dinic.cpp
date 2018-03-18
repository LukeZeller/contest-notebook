/*
* Description: Dinic's algorithm for max flow
* Demo: space efficient capacity/flow storage, flow can be reset
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 1231231234; //PS: needs to be 1e18 for long long flow
const double EPS = 1e-9;

struct edge {int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT; /*PS*/

vector <flowT> capacities, flow;
vector <int> level, startEdge;
void addEdge(graph &g, int from, int to, flowT capacity)
{
    g[from].push_back({to, (int) flow.size()});
    capacities.push_back(capacity), flow.push_back(0);
    g[to].push_back({from, (int) flow.size()});
    capacities.push_back(0), flow.push_back(0);
}

flowT residual(int id){return capacities[id] - flow[id];}

bool buildLevelGraph(graph &g, int source, int sink)
{
    queue <int> q;
    q.push(source);
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        for (edge e: g[curr]) if (level[e.to] == -1 and residual(e.id) > EPS)
        {
            q.push(e.to);
            level[e.to] = level[curr] + 1;
        }
    }
    return level[sink] != -1;
}

flowT blockingFlow(graph &g, int curr, int sink, flowT sent = INF)
{
    if (curr == sink) return sent;
    for (; startEdge[curr] < g[curr].size(); startEdge[curr]++)
    {
        edge e = g[curr][startEdge[curr]];
        if (level[e.to] == level[curr] + 1 and residual(e.id) > EPS)
        {
            flowT augment = blockingFlow(g, e.to, sink, min(sent, residual(e.id)));
            if (augment > EPS)
            {
                flow[e.id] += augment;
                flow[e.id ^ 1] -= augment;
                return augment;
            }
        }
    }
    return 0;
}

flowT dinic(graph &g, int source, int sink)
{
    flowT res = 0;
    level.resize(g.size()), startEdge.resize(g.size());
    while (buildLevelGraph(g, source, sink))
    {
        fill(startEdge.begin(), startEdge.end(), 0);
        while (flowT delta = blockingFlow(g, source, sink)) res += delta;
    }
    return res;
}

int main()
{
    int n = 5;
    graph g(n + 2);

    int source = n, sink = n + 1;
    addEdge(g, source, 0, 5), addEdge(g, source, 1, 5), addEdge(g, source, 2, 3);
    addEdge(g, 0, 3, 1), addEdge(g, 0, 4, 4), addEdge(g, 1, 4, 2), addEdge(g, 2, 4, 1);
    addEdge(g, 3, sink, 10), addEdge(g, 4, sink, 5);

    //Expected: 6
    cout<<dinic(g, source, sink)<<'\n';

    addEdge(g, 1, 0, 5);
    fill(flow.begin(), flow.end(), 0);

    //Expected: 6
    cout<<dinic(g, source, sink)<<'\n';

    addEdge(g, 0, sink, 5);
    fill(flow.begin(), flow.end(), 0);

    //Expected: 11
    cout<<dinic(g, source, sink)<<'\n';

    return 0;
}
