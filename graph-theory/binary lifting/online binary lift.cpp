/*
* Description: online binary lifting
* Demo: maxPath() finds maximal weight path starting at given node (going up) below threshold
*       pathDistance() finds weight of path starting at given node (going up) going up d edges
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const int MAXN = 100005; /*PS*/
const ll INF = 123123123123123123;

struct binaryLift
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <vector<ll>> sums; /*PS*/

    binaryLift()
    {
        sz = MAXN, calcHeight(), table.resize(sz, vector<int>(h, -1));
        sums.resize(sz, vector<ll>(h)); /*PS*/
    }

    void calcHeight(){while (1 << h < sz) h++;}

    void addEdge(int par, int curr, int w)
    {
        table[curr][0] = par;
        sums[curr][0] = w; /*PS*/
        for (int i = 1; i < h; i++) if (table[curr][i - 1] != -1)
        {
            table[curr][i] = table[table[curr][i - 1]][i - 1];
            sums[curr][i] = sums[table[curr][i - 1]][i - 1] + sums[curr][i - 1]; /*PS*/
        }
    }

    ll pathDistance(int bot, int d) //PS: easily modified to maxOnPath(), etc
    {
        ll acc = 0;
        int curr = bot;
        for (int i = h - 1; i >= 0; i--) if (table[curr][i] != -1)
        {
            if ((1 << i) & d)
            {
                acc += sums[curr][i];
                curr = table[curr][i];
                d -= 1 << i;
            }
        }
        if (d != 0) return INF; //depth not enough to go up d steps
        return acc;
    }

    ll maxPath(int bot, int threshold) /*PS*/
    {
        ll acc = 0; //PS: INF/-INF for min/max queries
        int curr = bot;
        for (int i = h - 1; i >= 0; i--) if (table[curr][i] != -1)
        {
            if (acc + sums[curr][i] <= threshold)
            {
                acc += sums[curr][i];
                curr = table[curr][i];
            }
        }
        return acc;
    }
};

int main()
{
    binaryLift bl;
    bl.addEdge(0, 1, 1), bl.addEdge(0, 2, 3);
    bl.addEdge(1, 3, 7), bl.addEdge(1, 4, 3), bl.addEdge(4, 5, -9);
    //Expected: 0 0 1
    cout<<bl.maxPath(0, 5)<<" "<<bl.maxPath(1, 0)<<" "<<bl.maxPath(1, 1)<<'\n';
    //Expected: 0 7 8 8
    cout<<bl.maxPath(3, 6)<<" "<<bl.maxPath(3, 7)<<" "<<bl.maxPath(3, 8)<<" "<<bl.maxPath(3, 9)<<'\n';
    //Expected: 4 3
    cout<<bl.maxPath(4, 100)<<" "<<bl.maxPath(2, 3)<<'\n';
    //Expected: INF INF INF INF
    cout<<bl.pathDistance(0, 1)<<" "<<bl.pathDistance(1, 2)<<" "<<bl.pathDistance(4, 5)<<" "<<bl.pathDistance(5, 4)<<'\n';
    //Expected: 1 3 8
    cout<<bl.pathDistance(1, 1)<<" "<<bl.pathDistance(2, 1)<<" "<<bl.pathDistance(3, 2)<<'\n';
    //Expected: 4 3 -5
    cout<<bl.pathDistance(4, 2)<<" "<<bl.pathDistance(4, 1)<<" "<<bl.pathDistance(5, 3)<<'\n';

    return 0;
}
