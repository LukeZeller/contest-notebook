/*
* Description: iterative segment tree
* Demo: Sum range query, increment point update
*/

#include <iostream>
#include <vector>

using namespace std;

struct node /*PS*/
{
    int sum = 0; //PS: remember max -> -INF, min -> +INF, sum -> 0

    void init(int i){sum = i;}
    void modify(int v){sum += v;}

    node combine(node &o)
    {
        node res;
        res.sum = sum + o.sum;
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;
    vector <int> v; /*PS*/

    segmentTree(vector <int> &ve)
    {
        v = ve, sz = v.size(); /*PS*/
        elements.resize(2 * sz);
        build();
    }

    void build()
    {
        for (int i = 0; i < sz; i++) elements[i + sz].init(v[i]); //PS: can also use some defaultValue
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    void modify(int p, int v)
    {
        elements[p += sz].modify(v);
        for (p >>= 1; p >= 1; p >>= 1)
        {
            elements[p] = elements[p << 1].combine(elements[p << 1 | 1]);
        }
    }

    int query(int l, int r)
    {
        node lacc, racc;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) lacc = lacc.combine(elements[l]);
            if (!(r & 1)) racc = elements[r].combine(racc);
        }
        return lacc.combine(racc).sum; /*PS*/
    }
};

int main()
{
    vector <int> a = {1, 3, 5, 2, 9};
    segmentTree st(a);

    //Expected: 20
    cout<<st.query(0, 4)<<'\n';

    //Expected: 4 8 7 11
    for (int i = 0; i + 1 < 5; i++) cout<<st.query(i, i + 1)<<" ";
    cout<<'\n';

    //a: {3, 3, 10, 2, -1};
    st.modify(0, 2);
    st.modify(2, 5);
    st.modify(4, -10);

    //Expected: 16
    cout<<st.query(0, 2)<<'\n';

    //Expected: -1
    cout<<st.query(4, 4)<<'\n';

    return 0;
}
