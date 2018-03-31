/*
* Description: divide and conquer on trees
* Demo: process(), solveSubtree(), refresh() allow for finding solution separately from updating parameters
*/

#include <iostream>
#include <vector>

using namespace std;

struct edge{int to, w;};
typedef vector <vector<edge>> graph;

struct centroidDecomposition
{
    int sz;
    graph g;
    vector <int> sizes, blocked;

    int sol = 0; //PS: max: -INF, min: INF, sum: 0
    //PS: other PS parameters

    centroidDecomposition(graph &gr)
    {
        g = gr, sz = g.size();
        sizes.resize(sz), blocked.resize(sz);
        //PS: Initialize PS parameters
        decompose(0);
    }

    void decompose(int curr, int prev = -1)
    {
        curr = findCentroid(calcSize(curr), curr);
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
            {
                curr = e.to; break;
            }
        }
        return curr;
    }

    void solveNode(int curr, int prev = -1)
    {
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            solveSubtree(e.to, curr);
            refresh(e.to, curr);
        }
    }

    template <class Operation>
    void process(int curr, int prev, Operation op) //PS: only need following functions if updates cannot be done while solving
    {
        op(); //PS: parameters should be info needed to find subtree solution
        for (edge e: g[curr]) if (e.to != prev and !blocked[e.to])
        {
            process(e.to, curr, op); /*PS*/
        }
    }

    void solveSubtree(int curr, int prev)
    {
        process(curr, prev, [this]()
        {
            //PS: modify value of sol here
        });
    }

    void refresh(int curr, int prev)
    {
        process(curr, prev, [this]()
        {
            //PS: update PS parameters here
        });
    }
};

int main()
{
    graph g;
    centroidDecomposition cd(g);
    cout<<cd.sol<<'\n';

    return 0;
}
