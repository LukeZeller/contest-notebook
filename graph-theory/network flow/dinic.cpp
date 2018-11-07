/*
* Description: dinic's algorithm for max flow
* Demo: space efficient capacity/flow storage, flow can be reset
*/

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

typedef int flowT; /*PS*/
struct dinic
{
    int sz;
    graph g;
    vector <flowT> capacities, flow;
    vector <int> level, startEdge;

    dinic(int s) : sz(s), g(sz), level(sz), startEdge(sz) {}

    void addEdge(int from, int to, flowT capacity)
    {
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }

    flowT residual(int id){return capacities[id] - flow[id];}

    bool buildLevelGraph(int source, int sink)
    {
        queue <int> q;
        q.push(source);
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            for (edge e: g[curr]) if (level[e.to] == -1 and residual(e.id) > 0)
            {
                q.push(e.to);
                level[e.to] = level[curr] + 1;
            }
        }
        return level[sink] != -1;
    }

    flowT blockingFlow(int curr, int sink, flowT sent = INF)
    {
        if (curr == sink) return sent;
        for (; startEdge[curr] < g[curr].size(); startEdge[curr]++)
        {
            edge e = g[curr][startEdge[curr]];
            if (level[e.to] == level[curr] + 1 and residual(e.id) > 0)
            {
                flowT augment = blockingFlow(e.to, sink, min(sent, residual(e.id)));
                if (augment > 0)
                {
                    flow[e.id] += augment;
                    flow[e.id ^ 1] -= augment;
                    return augment;
                }
            }
        }
        return 0;
    }

    flowT maxflow(int source, int sink)
    {
        flowT res = 0;
        while (buildLevelGraph(source, sink))
        {
            fill(startEdge.begin(), startEdge.end(), 0);
            while (flowT delta = blockingFlow(source, sink)) res += delta;
        }
        return res;
    }
};

int main()
{
    int n = 5;
    dinic dnc(n + 2);

    int source = n, sink = n + 1;
    dnc.addEdge(source, 0, 5), dnc.addEdge(source, 1, 5), dnc.addEdge(source, 2, 3);
    dnc.addEdge(0, 3, 1), dnc.addEdge(0, 4, 4), dnc.addEdge(1, 4, 2), dnc.addEdge(2, 4, 1);
    dnc.addEdge(3, sink, 10), dnc.addEdge(4, sink, 5);

    //Expected: 6
    cout<<dnc.maxflow(source, sink)<<'\n';

    dnc.addEdge(1, 0, 5);
    fill(dnc.flow.begin(), dnc.flow.end(), 0);

    //Expected: 6
    cout<<dnc.maxflow(source, sink)<<'\n';

    dnc.addEdge(0, sink, 5);
    fill(dnc.flow.begin(), dnc.flow.end(), 0);

    //Expected: 11
    cout<<dnc.maxflow(source, sink)<<'\n';
}
