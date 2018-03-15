/*
* Description: merge sort tree
* Demo: orderOf (position of value in sorted range), kthElement (kth value in sorted range)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node : vector<int>
{
    void init(int i){assign(1, i);}

    node combine(node &o)
    {
        node res;
        res.resize(size() + o.size());
        merge(begin(), end(), o.begin(), o.end(), res.begin());
        return res;
    }
};

struct segmentTree
{
    int sz;
    vector <node> elements;
    vector <int> v, sorted; //PS: sorted only needed for kthElement

    segmentTree(vector <int> &ve)
    {
        v = ve, sorted = ve, sz = v.size();
        elements.resize(2 * sz);
        build();
        sort(sorted.begin(), sorted.end());
    }

    void build()
    {
        for (int i = 0; i < sz; i++) elements[i + sz].init(v[i]);
        for (int i = sz - 1; i >= 1; i--)
        {
            elements[i] = elements[i << 1].combine(elements[i << 1 | 1]);
        }
    }

    int orderOf(vector <int> &v, int k)
    {
        return lower_bound(v.begin(), v.end(), k) - v.begin();
    }

    int orderOf(int l, int r, int k)
    {
        int acc = 0;
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) acc += orderOf(elements[l], k);
            if (!(r & 1)) acc += orderOf(elements[r], k);
        }
        return acc;
    }

    int kthElement(int l, int r, int k)
    {
        int bl = 0, br = sz - 1;
        while (bl < br)
        {
            int bm = (bl + br + 1) / 2;
            if (orderOf(l, r, sorted[bm]) <= k)
            {
                bl = bm;
            }
            else
            {
                br = bm - 1;
            }
        }
        return sorted[bl];
    }
};

int main()
{
    vector <int> a = {1, 5, 2, 6, 3, 8, 4};
    segmentTree st(a);

    //Expected: 6
    cout<<st.kthElement(3, 3, 0)<<'\n';

    //Expected: 8
    cout<<st.kthElement(0, 6, 7)<<'\n';

    //Expected: 6
    cout<<st.orderOf(0, 6, 7)<<'\n';

    //Expected: 6
    cout<<st.orderOf(0, 6, 8)<<'\n';

    //Expected: 7
    cout<<st.orderOf(0, 6, 9)<<'\n';

    return 0;
}
