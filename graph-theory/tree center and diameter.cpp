/*
* Description: finding the center/diameter of a tree by deleting leaves
* Demo: findCenters() returns vector containing the centers (1 or 2) of a tree - the nodes w/ the maximal shortest path to any other node
*       diameter() finds the longest sh. path between any two nodes
*/

vector <int> findCenters(graph &g) // finds center(s) of undirected tree
{
    int n = g.size(), removed = 0;
    vector <int> degree(n), leaves;
    for (int i = 0; i < n; i++)
    {
        degree[i] = g[i].size();
        if (degree[i] <= 1)
            leaves.push_back(i), removed++;
    }
    while (removed < n)
    {
        vector <int> temp;
        for (int leaf: leaves)
            for (edge e: g[leaf]) if (--degree[e.to] == 1)
                temp.push_back(e.to), removed++;
        leaves = temp;
    }
    return leaves;
}

pair <int, int> maxDistance(graph &g, int curr, int prev = -1) // returns (distance, furthest node) pair, where distance is maximal path length from curr going away from prev (if prev != -1)
{
    pair <int, int> res = {-1, curr};
    for (edge e: g[curr]) if (e.to != prev)
        res = max(res, maxDistance(g, e.to, curr));
    res.first++;
    return res;
}

int diameter(graph &g) // returns length of longest simple path between two nodes in undirected tree
{
    int center = findCenters(g)[0];
    int mx1 = 0, mx2 = 0;
    for (edge e: g[center])
    {
        int possible = 1 + maxDistance(g, e.to, center).first;
        if (possible > mx1)
            tie(mx1, mx2) = make_pair(possible, mx1);
        else if (possible > mx2)
            mx2 = possible;
    }
    return mx1 + mx2;
}

int main()
{
    graph g(16);
    g[0] = {{1}, {2}, {3}},  g[1] = {{0}, {4}, {5}}, g[2] = {{0}}, g[3] = {{0}};
    g[4] = {{1}}, g[5] = {{1}, {6}, {7}}, g[6] = {{5}, {8}, {9}}, g[7] = {{5}, {10}};
    g[8] = {{6}}, g[9] = {{6}, {11}}, g[10] = {{7}, {12}}, g[11] = {{9}, {13}}, g[12] = {{10}, {14}};
    g[13] = {{11}}, g[14] = {{12}, {15}}, g[15] = {{14}};
    // Expected: 9 3 13
    cout << diameter(g) << " " << maxDistance(g, 6, 5).first << " " << maxDistance(g, 6, 5).second << '\n';
    // Expected: 6 15 5 5
    cout << maxDistance(g, 6, 9).first << " " << maxDistance(g, 6, 9).second << " " << maxDistance(g, 5).first << " " << maxDistance(g, 7).first << '\n';
    // Expected: 5 7
    for (int center: findCenters(g))
        cout << center << " ";
    cout << '\n';

    graph g2(3);
    g2[0] = {{1}}, g2[1] = {{0}, {2}}, g2[2] = {{1}};
    // Expected: 1
    for (int center: findCenters(g2))
        cout << center << " ";
    cout << '\n';
}
