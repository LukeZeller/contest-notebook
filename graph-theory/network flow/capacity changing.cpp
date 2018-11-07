/*
* Description: Changing capacity of edges in flow class (works for both dinic/ffa)
*/

/*
* add "vector<vector<int>> indices" to flow class, and initialize it to be sz x sz in constructor
* modify addEdge() as follows, and add changeCapacity() function to class
*/
void addEdge(int from, int to, flowT capacity)
{
    if (indices[from][to] != -1)
        changeCapacity(from, to, capacity);
    else
    {
        indices[from][to] = flow.size();
        g[from].push_back({to, (int) flow.size()});
        capacities.push_back(capacity), flow.push_back(0);

        indices[to][from] = flow.size();
        g[to].push_back({from, (int) flow.size()});
        capacities.push_back(0), flow.push_back(0);
    }
}

void changeCapacity(int from, int to, flowT delta)
{
    if (indices[from][to] != -1)
        capacities[indices[from][to]] += delta;
}
