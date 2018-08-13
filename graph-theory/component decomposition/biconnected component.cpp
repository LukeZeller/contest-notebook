/*
* Description: tarjan's algorithm for biconnected components
* Demo: cutVertex/bridge store cut vertices and bridges, components stores edge biconnected components, category[i] is component # for node i
        br[i] is true iff edge i is a bridge, cv[i] is true iff vertex i is a cut vertex
*/

struct edge{int to, id;};
typedef vector<vector<edge>> graph;

struct tarjanBCC
{
    int n, m = 0, sz = 0; //sz is # of bcc -> caution!! don't use components.size()
    graph g;
    vector <int> depths, lowlinks, cutVertex, bridge; /*PS*/
    vector <bool> cv, br; /*PS*/
    vector <vector<int>> components; vector <int> category; /*PS*/

    tarjanBCC(graph &gr)
    {
        g = gr, n = g.size(), getEdge();
        depths.resize(n, -1), lowlinks.resize(n);
        cv.resize(n), br.resize(m), components.resize(n), category.resize(n); /*PS*/
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
        components[sz].push_back(curr), category[curr] = sz;
        for (edge e: g[curr]) if (depths[e.to] != -1 and !br[e.id])
            categorize(e.to);
    }
};

vector <pair<int, int>> edgeList;
void addEdge(graph &g, int i, int j, int id)
{
    g[i].push_back({j, id});
    g[j].push_back({i, id});
    edgeList.push_back({i, j});
}

int main()
{
    int n = 9;

    graph g(n);
    addEdge(g, 0, 2, 0), addEdge(g, 2, 4, 1), addEdge(g, 0, 4, 2);
    addEdge(g, 1, 3, 3), addEdge(g, 3, 5, 4), addEdge(g, 5, 1, 5);
    addEdge(g, 6, 8, 6), addEdge(g, 6, 7, 7), addEdge(g, 7, 8, 8);
    addEdge(g, 2, 5, 9), addEdge(g, 5, 7, 10);

    auto bcc = tarjanBCC(g);

    //Expected: 2 5 7
    for (int i: bcc.cutVertex) cout<<i<<" ";
    cout<<'\n';

    //Expected: (2, 5) (5, 7)
    for (int j: bcc.bridge) cout<<"("<<edgeList[j].first<<", "<<edgeList[j].second<<") ";
    cout<<'\n';

    /*Expected:
    * 0 2 4
    * 1 3 5
    * 6 7 8
    */
    for (int i = 0; i < bcc.sz; i++)
    {
        for (int j: bcc.components[i]) cout<<j<<" ";
        cout<<'\n';
    }

    addEdge(g, 2, 7, 11);
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
}
