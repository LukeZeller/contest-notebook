/*
* Description: Tour ordering for skipping subtrees
* Demo: Tour will visit each node once - ordered[i] stores the i-th node visited during the tour
*       jump[i] stores the ordered index of the first node visited after i that is not in i's subtree
* Note: jump[i] = n indicates that there are no nodes after i other than those in i's subtree
*       in dynamic programming, dp[n] is usually the solution (represents ending outside the tree)
*        and dp[i] represents the solution using the i-th visited node AKA ordered[i] (NOT node i)
*/

int timer;
vector <int> jump, ordered;
void tour(graph &g, int curr) // Caution !! Make sure jump and ordered are both assigned size n, and timer is set to 0 beforehand
{
    ordered[timer++] = curr;
    for (edge e: g[curr])
        tour(g, e.to);
    jump[curr] = timer;
}

int main()
{
    int n = 5;
    graph g(n);
    g[0] = {{1}, {2}};
    g[1] = {{3}, {4}};

    jump.assign(n, 0), ordered.assign(n, 0);
    timer = 0;
    tour(g, 0);

    // Expected: 0 1 3 4 2
    for (int i: ordered)
        cout << i << " ";
    cout << '\n';
    // Expected: 5 2 5 4 2
    for (int i = 0; i < n; i++)
        cout << ((jump[i] < n) ? ordered[jump[i]] : n) << " ";
    cout << '\n';
}
