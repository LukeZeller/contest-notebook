/*
* Description: toposort using dfs
* Demo: returns pair where first element is true iff there is no directed cycle in graph, second element is toposorted order of vertices (only valid if no cycle/if bool is true)
*/

bool hasCycle(graph &g, int curr, vector <int> &color, deque <int> &topo)
{
    if (color[curr])
        return color[curr] == 2 ? true : false;
    color[curr] = 2;

    for (edge e: g[curr])
        if (hasCycle(g, e.to, color, topo))
            return true;

    color[curr] = 1;
    topo.push_front(curr);
    return false;
}

pair <bool, deque<int>> toposort(graph &g)
{
    deque <int> topo;
    vector <int> color(g.size());
    for (int i = 0; i < g.size(); i++)
        if (hasCycle(g, i, color, topo))
            return {false, topo};
    return {true, topo};
} // false: has cycle, true: no cycle
