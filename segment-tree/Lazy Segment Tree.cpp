/*
* Description: lazy propagation segment tree
* Demo: increment range update, max range query
*/

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1231231234;

struct node
{
    int maxVal, lazy; /*PS*/
    int lb, rb, isLazy;
    node *l, *r;

    node() : l(NULL), r(NULL) {maxVal = -INF, resetLazy();} //PS: remember max -> -INF, min -> +INF, sum -> 0
    node(node &a, node &b) : l(&a), r(&b) {refresh();}
    void init(int i){maxVal = i;} /*PS*/

    node* refresh()
    {
        maxVal = max(l -> maxVal, r -> maxVal); /*PS*/
        return this;
    }

    void pushLazy()
    {
        if (isLazy)
        {
            maxVal += lazy; /*PS*/
            if (lb != rb)
            {
                l -> setLazy(lazy), r -> setLazy(lazy);
            }
            resetLazy();
        }
    }

    void setLazy(int v) /*PS*/
    {
        lazy += v, isLazy = true;
    }

    void resetLazy() //PS: set lazy s.t. setLazy() on non-lazy node is valid
    {
        lazy = 0, isLazy = false;
    }
};

struct segmentTree
{
    int sz;
    node* root;
    int defaultValue = 0; //can also use values from some vector

    segmentTree(int s)
    {
        root = new node(), sz = s;
        build(root, 0, sz - 1);
    }

    node combine(node a, node b)
    {
        node acc;
        acc.l = &a, acc.r = &b;
        return *(acc.refresh());
    }

    void build(node* &curr, int l, int r)
    {
        curr -> lb = l, curr -> rb = r;
        if (l == r) {curr -> init(defaultValue); return;}
        int m = (l + r) >> 1;
        build(curr -> l = new node(), l, m), build(curr -> r = new node(), m + 1, r);
        curr -> refresh();
    }

    int query(int l, int r) {return query(root, l, r).maxVal;} //PS
    node query(node* &curr, int l, int r)
    {
        curr -> pushLazy();
        if (curr -> lb > r or curr -> rb < l) return node();
        if (curr -> lb >= l and curr -> rb <= r) return *curr;
        node lq = query(curr -> l, l, r), rq = query(curr -> r, l, r);
        return node(lq, rq);
    }

    void modify(int l, int r, int v) {modify(root, l, r, v);}
    void modify(node* &curr, int l, int r, int v)
    {
        curr -> pushLazy();
        if (curr -> lb > r or curr -> rb < l) return;
        if (curr -> lb >= l and curr -> rb <= r)
        {
            curr -> setLazy(v);
            curr -> pushLazy();
            return;
        }
        modify(curr -> l, l, r, v), modify(curr -> r, l, r, v);
        curr -> refresh();
    }
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
