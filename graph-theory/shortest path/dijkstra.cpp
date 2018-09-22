/*
* Description: dijkstra's algorithm for shortest path
* Demo: returns vector of distances from source to all nodes in graph
*/

const ll INF = 1e18;

struct edge {int to, w;}; /*PS*/
typedef vector <vector<edge>> graph;

struct node
{
    int index; ll distance; /*PS*/

    bool operator > (const node &o) const
    {
        return make_pair(distance, index) > make_pair(o.distance, o.index);
    }
};

vector <ll> dijkstra(graph &g, int s)
{
    priority_queue <node, vector<node>, greater<node>> pq;
    vector <ll> distances(g.size(), INF); 
    vector <bool> visited(g.size());

    pq.push({s, 0});
    distances[s] = 0;
    while(!pq.empty())
    {
        node curr = pq.top();
        pq.pop();

        if (visited[curr.index]) continue;
        visited[curr.index] = true;

        for (edge e: g[curr.index]) if (curr.distance + e.w < distances[e.to])
        {
            distances[e.to] = curr.distance + e.w;
            pq.push({e.to, distances[e.to]});
        }
    }
    return distances;
}

void addEdge(graph &g, int i, int j, int w)
{
    g[i].push_back({j, w});
    g[j].push_back({i, w});
}

int main()
{
    graph g(6);

    addEdge(g, 0, 2, 1), addEdge(g, 0, 1, 5), addEdge(g, 1, 2, 5), addEdge(g, 2, 3, 2),
    addEdge(g, 1, 4, 7), addEdge(g, 3, 5, 100), addEdge(g, 4, 5, 2);

    //Expected: 0 5 1 3 12 14
    for (auto dist: dijkstra(g, 0))
    {
        cout<<dist<<" ";
    }
    cout<<'\n';

    return 0;
}
