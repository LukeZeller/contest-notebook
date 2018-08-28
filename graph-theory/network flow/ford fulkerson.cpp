/*
* Description: ford fulkerson algorithm for max flow
* Demo: space efficient capacity/flow storage, flow can be reset
*/

#include <bits/stdc++.h>

using namespace std;

const int INF = 1231231234;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef int flowT;

struct fordfulkerson
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> visited;

    fordfulkerson(int s)
    {
        sz = s, g.resize(sz);
        visited.resize(sz);
    }

    void addEdge(int from, int to, flowT capacity)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }

    flowT residual(int id){return capacities[id] - flow[id];}

    int dfs(int curr, int sink, flowT sent = INF)
    {
        if (curr == sink)
            return sent;

        if(visited[curr])
            return 0;
        visited[curr] = true;

        for (edge e: g[curr]) if (residual(e.id) > 0)
        {
            flowT augment = dfs(e.to, sink, min(sent, residual(e.id)));
            if (augment > 0)
            {
                flow[e.id] += augment;
                flow[e.id ^ 1] -= augment;
                return augment;
            }
        }
        return 0;
    }

    flowT maxflow(int source, int sink)
    {
        flowT res = 0, delta;
        visited.assign(sz, 0);
        while(delta = dfs(source, sink))
        {
            res += delta;
            fill(visited.begin(), visited.end(), 0);
        }
        return res;
    }
};

int main()
{
    int n = 5;
    fordfulkerson ffa(n + 2);

    int source = n, sink = n + 1;
    ffa.addEdge(source, 0, 5), ffa.addEdge(source, 1, 5), ffa.addEdge(source, 2, 3);
    ffa.addEdge(0, 3, 1), ffa.addEdge(0, 4, 4), ffa.addEdge(1, 4, 2), ffa.addEdge(2, 4, 1);
    ffa.addEdge(3, sink, 10), ffa.addEdge(4, sink, 5);

    // Expected: 6
    cout<<ffa.maxflow(source, sink)<<'\n';

    ffa.addEdge(1, 0, 5), ffa.addEdge(0, sink, 5);
    fill(ffa.flow.begin(), ffa.flow.end(), 0);

    //Expected: 11
    cout<<ffa.maxflow(source, sink)<<'\n';
}
