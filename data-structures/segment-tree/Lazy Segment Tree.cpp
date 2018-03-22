/*
* Description: lazy propagation segment tree
* Demo: increment range update, max range query
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1231231234

struct node
{
    int maxVal, lazy;
    bool isLazy;
    node *l, *r;

    node(){maxVal = -INF, resetLazy();} //PS: remember max -> -INF, min -> +INF, sum -> 0
    void combine(node &a, node &b){l = &a, r = &b, refresh();}
    void init(int i){maxVal = i;}

    void refresh()
    {
        maxVal = max(l -> maxVal, r -> maxVal); /*PS*/
    }

    void pushLazy(int lb, int rb)
    {
        if (isLazy)
        {
            maxVal += lazy; /*PS*/
            if (lb != rb) l -> setLazy(lazy), r -> setLazy(lazy);
            resetLazy();
        }
    }

    void setLazy(int v){lazy += v, isLazy = true;} /*PS*/
    void resetLazy(){lazy = 0, isLazy = false;} //PS: set lazy s.t. setLazy() on non-lazy node is valid
};

struct segmentTree
{
    int sz, defaultValue = 0; //can also use values from some vector
    vector <node> elements;
    vector <int> lb, rb;

    segmentTree(){}
    segmentTree(int s)
    {
        sz = s;
        elements.resize(4 * sz), lb.resize(4 * sz), rb.resize(4 * sz);
        build(0, sz - 1);
    }

    void build(int l, int r, int p = 1)
    {
        lb[p] = l, rb[p] = r;
        if (l == r) {elements[p].init(defaultValue); return;}
        int m = (l + r) >> 1;
        build(l, m, p << 1), build(m + 1, r, p << 1 | 1);
        elements[p].combine(elements[p << 1], elements[p << 1 | 1]);
    }

    int query(int l, int r){return query(l, r, 1).maxVal;} /*PS*/
    node query(int l, int r, int p)
    {
        push(p);
        if (lb[p] > r or rb[p] < l) return node();
        if (lb[p] >= l and rb[p] <= r) return elements[p];
        node res, ql = query(l, r, p << 1), qr = query(l, r, p << 1 | 1);
        res.combine(ql, qr);
        return res;
    }

    void modify(int l, int r, int v, int p = 1)
    {
        push(p);
        if (lb[p] > r or rb[p] < l) return;
        if (lb[p] >= l and rb[p] <= r)
        {
            elements[p].setLazy(v), push(p);
            return;
        }
        modify(l, r, v, p << 1), modify(l, r, v, p << 1 | 1);
        elements[p].refresh();
    }

    void push(int p){elements[p].pushLazy(lb[p], rb[p]);}
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
