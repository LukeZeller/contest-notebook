/*
* Description: DP for computing Steiner tree - Steiner tree is minimum cost tree that connects all terminal nodes
* Demo: returns table where dp[mask][i] = cost of tree connecting terminal nodes with on-bits in mask with root i (i could be a terminal node)
*       runs in O(n^3 + n * 3^t + n^2 * 2^t) time
*/

// n is # of vertices, t is # of terminal nodes, costs is adjacency matrix of edge weights, terminals contains list of the terminal node indices
vector <vector<int>> steinerTree(vector <vector<int>> &costs, vector <int> &terminals, int n, int t)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                costs[i][j] = min(costs[i][j], costs[i][k] + costs[k][j]);

    vector <vector<int>> dp(1 << t, vector <int>(n, INF)); // Caution !! 2 * INF must not overflow
    for (int i = 0; i < t; i++)
        dp[1 << i][terminals[i]] = 0;
    for (int bm = 1; bm < (1 << t); bm++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int sm = bm; sm > (sm ^ bm); sm = (sm - 1) & bm)
                dp[bm][i] = min(dp[bm][i], dp[sm][i] + dp[bm ^ sm][i]);
            if (dp[bm][i] == INF)
                continue;
            for (int j = 0; j < n; j++)
                dp[bm][j] = min(dp[bm][j], dp[bm][i] + costs[i][j]);
        }
    }
    return dp;
}

int main()
{
    int n = 5;
    vector <vector<int>> costs(n, vector<int>(n, INF));
    costs[0][1] = costs[1][0] = costs[1][2] = costs[2][1] = costs[3][2] = costs[2][3] = 1;
    costs[4][3] = costs[3][4] = 2, costs[1][4] = costs[4][1] = 5;

    vector <int> terminals = {0, 1, 4};
    int t = terminals.size();
    auto steiner = steinerTree(costs, terminals, n, t);

    int best = INF;
    for (int i = 0; i < n; i++)
        best = min(best, steiner[(1 << t) - 1][i]);
    // Expected: 5
    cout << best << '\n';
}
