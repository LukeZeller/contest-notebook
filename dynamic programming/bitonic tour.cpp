/*
* Description: dp for bitonic tsp (tsp solution where path is monotone left then monotone right or vice-versa)
* Explanation: dp[i][j] (always i < j) = length of path (we close the loop at the end) from i to 1 leftward, then 1 to j rightward
*       if i is not j - 1, j - 1 must be on rightward path right before j -> find optimal [i .. 1 .. j - 1] then add j to path
*       if i is j - 1, we know j - 1 is on leftward path, find the optimal k < j - 1 s.t. k is immediately before j -> [j - 1 .. 1 .. k], j
*       so we can find length of ideal [k .. 1 .. j - 1] AKA dp[k][j - 1] and add kj length to this (assumes distances are symmetric)
* Dependency: Uses pt class (but only for a struct w/ x and y fields, could just use pair<int, int> instead)
*/

ld bitonicTour(vector <pt> &points) // Caution !! Assumes that distances are symmetric -> dist[i][j] = dist[j][i];
{
    int n = points.size();
    if (n < 2)
        return 0;

    auto cmp = [](const pt &a, const pt &b) {
        return tie(a.x, a.y) < tie(b.x, b.y);
    };
    sort(points.begin(), points.end(), cmp);

    vector <vector<ld>> dp(n, vector<ld>(n, INF)), costs(n, vector<ld>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            auto dx = points[i].x - points[j].x, dy = points[i].y - points[j].y;
            costs[i][j] = sqrt(dx * dx + dy * dy);
        }
    }

    dp[0][1] = costs[0][1];
    for (int j = 2; j < n; j++)
    {
        for (int i = 0; i < j; i++)
        {
            if (i < j - 1)
                dp[i][j] = dp[i][j - 1] + costs[j - 1][j]; //
            else
            {
                for (int k = 0; k < j - 1; k++)
                    dp[j - 1][j] = min(dp[j - 1][j], dp[k][j - 1] + costs[k][j]);
            }
        }

    }
    return dp[n - 2][n - 1] + costs[n - 2][n - 1];
}
