/*
* Description: fenwick tree
* Demo: range sum query, point increment update
*/

#include <iostream>
#include <vector>

using namespace std;

struct fenwickTree
{
    vector <int> elements;

    fenwickTree(int s)
    {
        elements.resize(s + 1);
    }

    void modify(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i)) elements[i] += v; /*PS*/
    }

    int query(int i)
    {
        int ans = 0;
        for (i++; i > 0; i -= i & (-i)) ans += elements[i]; /*PS*/
        return ans;
    }

    int query(int l, int r) {return query(r) - query(l - 1);}
};

int main()
{
    fenwickTree ft(100);

    ft.modify(4, 100);
    ft.modify(0, 3);
    ft.modify(99, 20);
    ft.modify(0, 2);

    //Expected: 5
    cout<<ft.query(0, 0)<<'\n';

    //Expected: 105
    cout<<ft.query(0, 4)<<'\n';

    //Expected: 20
    cout<<ft.query(95, 99)<<'\n';

    //Expected: 0
    cout<<ft.query(5, 10)<<'\n';

    return 0;
}
