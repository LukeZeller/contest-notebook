/*
* Description: shortest path faster algorithm for single source shortest path with negative edges
* Demo: Returns pair where first value is true iff there are no reachable negative cycles, and second value is array of distances from source s to each node
*       array of distances is not valid if there is a reachable negative cycle -> check bool value before using distances
*/

struct edge{int to, w;};
typedef vector <vector<edge>> graph;

pair <bool, vector <ll>> spfa(graph &g, int s) // PS: bool return only needed if negative cycles need to be checked for
{
    int n = g.size();
    vector <ll> distances(n, INF);
    vector <int> inq(n), counts(n); // PS: counts only needed to detect negative cycles
    queue <int> q;

    distances[s] = 0;
    q.push(s);
    inq[s] = true;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        inq[curr] = false;
        for (edge e: g[curr])
        {
            if (distances[curr] + e.w < distances[e.to])
            {
                distances[e.to] = distances[curr] + e.w;
                if (!inq[e.to])
                {
                    q.push(e.to);
                    inq[e.to] = true;
                    if (++counts[e.to] > n) // PS: same as above
                        return {false, distances};
                }
            }
        }
    }
    return {true, distances};
}

int main()
{
    graph g(5);
    g[0].push_back({1, 7}), g[1].push_back({2, -3}), g[1].push_back({3, -1});
    g[0].push_back({2, 5}), g[2].push_back({4, 2}), g[3].push_back({4, -1});
    auto distances = spfa(g, 0);
    // Expected: 1
    cout << distances.first << '\n';
    // Expected: 0 7 4 6 5
    for (int i = 0; i < 5; i++)
        cout << distances.second[i] << " ";
    cout << '\n';

    graph g2(3);
    g2[0].push_back({1, 2}), g2[1].push_back({2, -1}), g2[2].push_back({0, -2});
    auto distances2 = spfa(g2, 0);
    // Expected: 0
    cout << distances2.first << '\n';
}
