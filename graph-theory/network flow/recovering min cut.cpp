/*
* Description: Recovering min-cut found by maxflow()
* Demo: cut[i] is true <=> i is in S (partition containing source), cut[i] is false <=> i is in T (partition containing sink)
*/

/*
* Add "vector <bool> cut" to flow class, initialize it to be sz-sized
* add findCut() to class as follows, call findCut() at the bottom of maxflow() or manually do it outside of class
*/
void findcut(int curr) /*PS*/
{
    if (cut[curr]) return;
    cut[curr] = true;
    for (edge e: g[curr]) if (!cut[e.to] and residual(e.id) > 0)
        findcut(e.to);
}
