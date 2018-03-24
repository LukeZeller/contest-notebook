/*
* Description: persistent segment tree
* Demo: increment range update, max range query, 
  modify (in segment tree) returns root of the new tree
*/

#include <iostream>
#include <vector>

using namespace std;

struct node /*PS*/
{
    int sum = 0;

    void init(int i){sum = i;}
    void modify(int v){sum += v;}
    node combine(const node &a, const node &b)
    {
        sum = a.sum + b.sum;
        return *this;
    }
} acc;

struct segmentTree
{
    node n;
    int lb, rb;
    segmentTree *l, *r;

    segmentTree(){}
    segmentTree(vector <int> &v) : segmentTree(0, v.size() - 1, v) {} //PS: can use def instead of v
    segmentTree(int ql, int qr, vector <int> &v) : lb(ql), rb(qr) /*PS*/
    {
        if (lb == rb){n.init(v[lb]); return;} /*PS*/
        int m = (lb + rb) >> 1;
        l = new segmentTree(lb, m, v), r = new segmentTree(m + 1, rb, v); //PS: same as above
        n.combine(l -> n, r -> n);
    }

    int query(int l, int r){return queryn(l, r).sum;} /*PS*/
    node queryn(int ql, int qr)
    {
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return n;
        return acc.combine(l -> queryn(ql, qr), r -> queryn(ql, qr));
    }

    segmentTree* modify(int qp, int v)
    {
        if (lb > qp or rb < qp) return this;
        if (lb == rb)
        {
            segmentTree* st = new segmentTree(*this);
            st -> n.modify(v);
            return st;
        }
        segmentTree* st = new segmentTree(*this);
        st -> l = l -> modify(qp, v), st -> r = r -> modify(qp, v);
        st -> n.combine(st -> l -> n, st -> r -> n);
        return st;
    }
};

typedef vector<segmentTree> segmentTreePs;
void modify(segmentTreePs &st, int p, int v)
{
    st.push_back(*st.back().modify(p, v));
}

int main()
{
    vector <int> a = {1, 3, 5, 2, 9};
    segmentTreePs st = {segmentTree(a)};

    //Expected: 20
    cout<<st[0].query(0, 4)<<'\n';

    //Expected: 4 8 7 11
    for (int i = 0; i + 1 < 5; i++) cout<<st[0].query(i, i + 1)<<" ";
    cout<<'\n';

    modify(st, 0, 2);
    //Expected: 11 13
    for (int i = 0; i < st.size(); i++) cout<<st[i].query(0, 3)<<" ";
    cout<<'\n';

    modify(st, 2, 5);
    //Expected: 9 11 16
    for (int i = 0; i < st.size(); i++) cout<<st[i].query(0, 2)<<" ";
    cout<<'\n';

    modify(st, 4, -10);
    //Expected: 9 9 9 -1
    for (int i = 0; i < st.size(); i++) cout<<st[i].query(4, 4)<<" ";
    cout<<'\n';

    return 0;
}
