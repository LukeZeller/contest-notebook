/*
* Description: tarjan's algorithm for biconnected components
* Demo: cutVertex/bridge store cut vertices and bridges, components stores edge biconnected components
*/

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to, id;};
typedef vector<vector<edge>> graph;
typedef vector<pair<int, int>> edgelist; /*PS*/

struct tarjanBCC
{
    int n, m = 0, sz = 0; //sz is # of bcc -> caution!! don't use components.size()
    graph g;
    vector <int> depths, lowlinks, cutVertex, bridge; /*PS*/
    vector <bool> cv, br; /*PS*/
    vector <vector<int>> components; /*PS*/

    tarjanBCC(graph &gr)
    {
        g = gr, n = g.size(), getEdge();
        depths.resize(n, -1), lowlinks.resize(n);
        cv.resize(n), br.resize(m), components.resize(n); /*PS*/
        getBcc();
    }

    void getEdge()
    {
        for (int i = 0; i < n; i++) m += g[i].size();
        m /= 2;
    }

    void getBcc()
    {
        for (int i = 0; i < n; i++) if (depths[i] == -1)
            dfs(i);
        for (int i = 0; i < n; i++) if (cv[i]) /*PS*/
            cutVertex.push_back(i);
        for (int i = 0; i < m; i++) if (br[i]) /*PS*/
            bridge.push_back(i);
        for (int i = 0; i < n; i++) if (depths[i] != -1) /*PS*/
            categorize(i), sz++;
    }

    bool dfs(int curr, int prev = -1, int pid = -1)
    {
        if (depths[curr] != -1)
        {
            lowlinks[prev] = min(lowlinks[prev], depths[curr]);
            return false;
        }

        lowlinks[curr] = depths[curr] = prev != -1 ? depths[prev] + 1 : 0;
        bool out = false; /*PS*/
        for (edge e: g[curr]) if (e.id != pid)
        {
            if (dfs(e.to, curr, e.id))
            {
                lowlinks[curr] = min(lowlinks[curr], lowlinks[e.to]);
                if (prev != -1 ? lowlinks[e.to] >= depths[curr] : out) cv[curr] = true; /*PS*/
                if (lowlinks[e.to] > depths[curr]) br[e.id] = true; /*PS*/
                out = true; /*PS*/
            }
        }
        return true;
    }

    void categorize(int curr) //PS: requires br
    {
        if (depths[curr] == -1) return;
        depths[curr] = -1;
        components[sz].push_back(curr);
        for (edge e: g[curr]) if (depths[e.to] != -1 and !br[e.id])
            categorize(e.to);
    }
};

void addEdge(graph &g, edgelist &el, int i, int j, int id)
{
    g[i].push_back({j, id});
    g[j].push_back({i, id});
    el.push_back({i, j});
}

int main()
{
    int n = 9;

    graph g(n);
    edgelist el;
    addEdge(g, el, 0, 2, 0), addEdge(g, el, 2, 4, 1), addEdge(g, el, 0, 4, 2);
    addEdge(g, el, 1, 3, 3), addEdge(g, el, 3, 5, 4), addEdge(g, el, 5, 1, 5);
    addEdge(g, el, 6, 8, 6), addEdge(g, el, 6, 7, 7), addEdge(g, el, 7, 8, 8);
    addEdge(g, el, 2, 5, 9), addEdge(g, el, 5, 7, 10);

    auto bcc = tarjanBCC(g);

    //Expected: 2 5 7
    for (int i: bcc.cutVertex) cout<<i<<" ";
    cout<<'\n';

    //Expected: (2, 5) (5, 7)
    for (int j: bcc.bridge) cout<<"("<<el[j].first<<", "<<el[j].second<<") ";
    cout<<'\n';

    /*Expected:
    * 0 2 4
    * 1 3 5
    * 5 7 8
    */

    for (int i = 0; i < bcc.sz; i++)
    {
        for (int j: bcc.components[i]) cout<<j<<" ";
        cout<<'\n';
    }

    addEdge(g, el, 2, 7, 11);
    bcc = tarjanBCC(g);

    //Expected: 2 5 7
    for (int i: bcc.cutVertex) cout<<i<<" ";
    cout<<'\n';

    //Expected: 0 1 2 3 4 5 6 7 8
    for (int i = 0; i < bcc.sz; i++)
    {
        for (int j: bcc.components[i]) cout<<j<<" ";
        cout<<'\n';
    }

    return 0;
}
