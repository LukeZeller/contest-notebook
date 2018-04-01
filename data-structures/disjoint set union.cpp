/*
* Description: disjoint set union w/ rank compression
* Demo: sameComponent (checks if i and j are in the same set), sizeComponent(returns size of set that contains i)
*/

#include <iostream>
#include <vector>

using namespace std;

struct disjointSetUnion
{
    int sz;
    vector <int> par, sizes; //PS: sizes is often not needed

    disjointSetUnion(int s)
    {
        sz = s;
        par.resize(sz), sizes.resize(sz);
        for (int i = 0; i < sz; i++) {par[i] = i, sizes[i] = 1;}
    }

    int findRoot(int i)
    {
        return par[i] == i ? i : (par[i] = findRoot(par[i]));
    }

    void unionElements(int i, int j)
    {
        sizes[findRoot(j)] += sizes[findRoot(i)]; /*PS*/
        par[findRoot(i)] = findRoot(j);
    }

    bool sameComponent(int i, int j) {return findRoot(i) == findRoot(j);} /*PS*/

    int sizeComponent(int i){return sizes[findRoot(i)];} /*PS*/
};

int main()
{
    disjointSetUnion dsu(100);

    dsu.unionElements(0, 5);
    dsu.unionElements(3, 4);
    dsu.unionElements(99, 98);
    dsu.unionElements(98, 3);

    //Expected: 4
    cout<<dsu.sizeComponent(3)<<'\n';

    //Expected: 1
    cout<<dsu.sameComponent(3, 99)<<'\n';

    //Expected: 0
    cout<<dsu.sameComponent(0, 4)<<'\n';

    //Expected: 2 2
    cout<<dsu.sizeComponent(5)<<" "<<dsu.sizeComponent(0)<<'\n';

    return 0;
}
