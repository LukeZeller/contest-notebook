/*
* Description: lazy propagation segment tree
* Demo: increment range update, max range query
*/

#include <iostream>
#include <vector>

using namespace std;

#define INF 1231231234

struct node /*PS*/
{
    int maxVal = -INF; //PS: max: -INF, min: INF, sum: 0

    void init(int i){maxVal = i;}
    node combine(const node &a, const node &b)
    {
        maxVal = max(a.maxVal, b.maxVal);
        return *this;
    }
} acc;

struct segmentTree
{
    node n;
    int lb, rb, lazy; bool isLazy;
    segmentTree *l, *r;

    segmentTree(){}
    segmentTree(int s, int d = 0) : segmentTree(0, s - 1, d) {} //PS: can use vector instead of d
    segmentTree(int ql, int qr, int d) : lb(ql), rb(qr)
    {
        resetLazy();
        if (lb == rb){n.init(d); return;}
        int m = (lb + rb) >> 1;
        l = new segmentTree(lb, m, d), r = new segmentTree(m + 1, rb, d);
        n.combine(l -> n, r -> n);
    }

    int query(int l, int r){return queryn(l, r).maxVal;} /*PS*/
    node queryn(int ql, int qr)
    {
        pushLazy();
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return n;
        return acc.combine(l -> queryn(ql, qr), r -> queryn(ql, qr));
    }

    void modify(int ql, int qr, int v)
    {
        pushLazy();
        if (lb > qr or rb < ql) return;
        if (lb >= ql and rb <= qr)
        {
            setLazy(v), pushLazy();
            return;
        }
        l -> modify(ql, qr, v), r -> modify(ql, qr, v);
        n.combine(l -> n, r -> n);
    }

    void pushLazy()
    {
        if (!isLazy) return;
        n.maxVal += lazy; /*PS*/
        if (lb != rb) l -> setLazy(lazy), r -> setLazy(lazy);
        resetLazy();
    }

    void setLazy(int v){lazy += v, isLazy = true;} /*PS*/
    void resetLazy(){lazy = 0, isLazy = false;} //PS: set lazy s.t. setLazy() on non-lazy node is valid
};

int main()
{
    segmentTree st(1000);
    st.modify(1, 5, 100);
    st.modify(5, 10, 150);
    st.modify(999, 999, 1000);

    //Expected: 250
    cout<<st.query(5, 5)<<'\n';

    //Expected: 1000
    cout<<st.query(0, 999)<<'\n';

    //Expected: 0
    cout<<st.query(11, 998)<<'\n';

    return 0;
}
