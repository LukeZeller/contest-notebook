/*
* Description: persistent segment tree (able to query old versions of tree without storing all of them separately)
* Demo: increment range update, max range query
*/

struct node
{
    int l = -1, r = -1, sum = 0;

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
    int sz;
    vector <node> elements;
    vector <int> roots;

    segmentTree(){}
    segmentTree(const vector <int> &v) : sz(v.size()) {roots.push_back(build(v, 0, sz - 1));} //PS: can use def instead of v

    int build(const vector <int> &v, int lb, int rb) /*PS*/
    {
        int ind = elements.size();
        elements.push_back(node());
        if (lb == rb)
            elements[ind].init(v[lb]);
        else
        {
            int m = (lb + rb) >> 1;
            int t1 = build(v, lb, m), t2 = build(v, m + 1, rb);
            elements[ind].l = t1, elements[ind].r = t2;
            elements[ind].combine(elements[t1], elements[t2]);
        }
        return ind;
    }

    int query(int version, int l, int r){return query(roots[version], l, r, 0, sz - 1).sum;} /*PS*/
    node query(int ind, int ql, int qr, int lb, int rb)
    {
        if (lb > qr or rb < ql) return node();
        if (lb >= ql and rb <= qr) return elements[ind];
        int m = (lb + rb) >> 1;
        return acc.combine(query(elements[ind].l, ql, qr, lb, m), query(elements[ind].r, ql, qr, m + 1, rb));
    }

    void modify(int p, int v){roots.push_back(modify(roots.back(), p, v, 0, sz - 1));}
    int modify(int ind, int qp, int v, int lb, int rb)
    {
        if (lb > qp or rb < qp) return ind;
        node nd(elements[ind]);
        if (lb == rb)
            nd.modify(v);
        else
        {
            nd.l = modify(elements[ind].l, qp, v, lb, (lb + rb) / 2);
            nd.r = modify(elements[ind].r, qp, v, (lb + rb) / 2 + 1, rb);
            nd.combine(elements[nd.l], elements[nd.r]);
        }
        int new_ind = elements.size();
        elements.push_back(nd);
        return new_ind;
    }
};

int main()
{
    vector <int> a = {1, 3, 5, 2, 9};
    segmentTree st(a);

    //Expected: 20
    cout<<st.query(0, 0, 4)<<'\n';

    //Expected: 4 8 7 11
    for (int i = 0; i + 1 < 5; i++) cout<<st.query(0, i, i + 1)<<" ";
    cout<<'\n';

    st.modify(0, 2);
    //Expected: 11 13
    for (int i = 0; i < st.roots.size(); i++) cout<<st.query(i, 0, 3)<<" ";
    cout<<'\n';

    st.modify(2, 5);
    //Expected: 9 11 16
    for (int i = 0; i < st.roots.size(); i++) cout<<st.query(i, 0, 2)<<" ";
    cout<<'\n';

    st.modify(4, -10);
    //Expected: 9 9 9 -1
    for (int i = 0; i < st.roots.size(); i++) cout<<st.query(i, 4, 4)<<" ";
    cout<<'\n';
}
