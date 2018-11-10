/*
* Description: divide and conquer on trees
* Demo: Finds # of pair of nodes that are exactly k-edges away from each other
*       solveSubtree()/refresh() allow for updating solution (solveSubtree) separately, before updating parameters (refresh)
*/

struct centroidDecomposition
{
    int sz;
    graph g;
    vector <int> sizes, blocked;

    ll sol = 0;
    int k; vector <int> numAtDistance; //PS: other PS parameters

    centroidDecomposition(graph &gr, int _k) : sz(gr.size()), g(gr), sizes(sz), blocked(sz) //PS: _k is a PS parameter
    {
        k = _k, numAtDistance.resize(k + 1); //PS: Initialize PS parameters
        decompose(0);
    }

    void decompose(int curr, int prev = -1)
    {
        curr = findCentroid(calcSize(curr), curr); // Can build centroid graph after this line, make edge from prev (if != -1) to curr, and set parent[curr] = prev (even if par = -1)
        blocked[curr] = true, solveNode(curr);
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
            decompose(e.to, curr);
    }

    int calcSize(int curr, int prev = -1)
    {
        sizes[curr] = 1;
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
            sizes[curr] += calcSize(e.to, curr);
        return sizes[curr];
    }

    int findCentroid(int total, int curr, int prev = -1)
    {
        for (int old; prev != curr; prev = old)
        {
            old = curr;
            for (edge e: g[curr]) if (e.to != prev and !blocked[e.to] and sizes[e.to] > total / 2)
                curr = e.to;
        }
        return curr;
    }

    void solveNode(int curr)
    {
        fill(numAtDistance.begin(), numAtDistance.end(), 0); // PS: reset any global parameters that are independent for each centroid
        numAtDistance[0] = 1; //PS: already have a "previous" path of length 0
        for (edge e: g[curr]) if (!blocked[e.to])
        {
            solveSubtree(e.to, curr); // Update solution for e.to branch using paths to previous branches'
            refresh(e.to, curr); // Update data about "previous branches" to include e.to
        }
    }

    template <class Operation>
    void process(int curr, int prev, int dist, Operation op) //PS: problem specific parameter (dist) used here to update numAtDistance and solution
    {
        op(dist); //PS: parameters should be info needed to find subtree solution/update global parameters (ex. numAtDistance)
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            process(e.to, curr, dist + 1, op); // PS: parameters change as mentioned above
        }
    }

    void solveSubtree(int branch, int centroid)
    {
        process(branch, centroid, 1, [this](int dist) //PS: third parameter is 1 b/c we start at child (AKA branch), which is already 1 distance from the centroid
        {
            if (dist <= k)
                sol += numAtDistance[k - dist];  //PS: modify value of sol here
        });
    }

    void refresh(int branch, int centroid)
    {
        process(branch, centroid, 1, [this](int dist) //PS: same idea as above about third parameter
        {
            if (dist <= k)
                numAtDistance[dist]++; //PS: update PS parameters here
        });
    }
};

int main()
{
    graph g(5);
    g[0] = {{1}}, g[1] = {{0}, {2}}, g[2] = {{1}, {3}, {4}}, g[3] = {{2}}, g[4] = {{2}};
    centroidDecomposition cd2(g, 2), cd3(g, 3);
    // Expected: 4 2
    cout << cd2.sol << " " << cd3.sol << '\n';
}
