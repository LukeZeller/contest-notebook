/*
* Description: finding the centroid of a tree by going into large subtrees
* Demo: centroid() returns a centroid - if the tree was rooted at the centroid, all subtrees would have size <= n / 2
* Note: there could be another centroid - both centroids are connected by an edge
*/

int calcSize(graph &g, vector <int> &sizes, int curr, int prev = -1)
{
    sizes[curr] = 1;
    for (edge e: g[curr]) if (e.to != prev)
        sizes[curr] += calcSize(g, sizes, e.to, curr);
    return sizes[curr];
}

 int findCentroid(graph &g, vector <int> &sizes, int total, int curr, int prev = -1)
{
    for (int old; prev != curr; prev = old)
    {
        old = curr;
        for (edge e: g[curr]) if (e.to != prev and sizes[e.to] > total / 2)
            curr = e.to;
    }
    return curr;
}

int centroid(graph &g)
{
    vector <int> sizes(g.size());
    int total = calcSize(g, sizes, 0);
    return findCentroid(g, sizes, total, 0);
}

int main()
{
    graph g(16);
    g[0] = {{1}, {2}, {3}},  g[1] = {{0}, {4}, {5}}, g[2] = {{0}}, g[3] = {{0}};
    g[4] = {{1}}, g[5] = {{1}, {6}, {7}}, g[6] = {{5}, {8}, {9}}, g[7] = {{5}, {10}};
    g[8] = {{6}};
    // Expected: 5
    cout << centroid(g) << endl;
}
