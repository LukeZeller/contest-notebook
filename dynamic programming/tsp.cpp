/*
* Description: dp for tsp
* Demo: finds the shortest hamiltonian cycle from starting node s, given cost matrix "costs"
*       can find shortest hamiltonian walk instead by setting dp[1 << i][i] = 0 & not adding costs[i][s] at PS marks, and removing parameter s
*/

template <typename T> T tsp(vector <vector<T>> &costs, int s)
{
    int n = costs.size();

    vector <vector<T>> dp(1 << n, vector<T>(n, INF));
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = costs[s][i]; /*PS*/

    for (int bm = 1; bm < (1 << n); bm++)
    {
        for (int i = 0; i < n; i++) if (bm & (1 << i))
        {
            int sm = bm - (1 << i);
            for (int j = 0; j < n; j++) if (sm & (1 << j))
               dp[bm][i] = min(dp[bm][i], dp[sm][j] + costs[j][i]); // if dp[bm][i] updated, then pred(i) = j
        }
    }

    T sol = INF;
    int FULL = (1 << n) - 1;
    for (int i = 0; i < n; i++)
        sol = min(sol, dp[FULL][i] + costs[i][s]); /*PS*/
    return sol;
}
