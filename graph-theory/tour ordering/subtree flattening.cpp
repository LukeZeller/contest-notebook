/*
* Description: Tour ordering for flattening subtrees
* Demo: Tour will visit each node twice, once when it first enters (in[i]) and once when it last leaves (out[i])
*       ordered[i] stores the i-th node visited during the tour
* Usage: The subtree of node i is stored in ordered between the indices in[i] and out[i] inclusive
*/

int timer;
vector <int> in, out, ordered;
void tour(graph &g, int curr) // Caution !! Make sure in/out are assigned size n, ordered is assigned size 2n, and timer is set to 0 beforehand
{
    in[curr] = timer++;
    ordered[in[curr]] = curr;
    for (edge e: g[curr])
        tour(g, e.to);
    out[curr] = timer++;
    ordered[out[curr]] = curr;
}

int main()
{
    int n = 5;
    graph g(n);
    g[0] = {{1}, {2}};
    g[1] = {{3}, {4}};

    in.assign(n, 0), out.assign(n, 0), ordered.assign(2 * n, 0);
    timer = 0;
    tour(g, 0);

    // Expected: 0 1 3 3 4 4 1 2 2 0
    for (int i: ordered)
        cout << i << " ";
    cout << '\n';
    // Expected: 0 9, 1 6, 7 8, 2 3, 4 5
    for (int i = 0; i < n; i++)
        cout << in[i] << " " << out[i] << '\n';
    cout << '\n';
}
