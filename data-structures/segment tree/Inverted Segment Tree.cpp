/*
* Description: inverted segment tree (range update, point query)
* Demo: sum range update, delta point query (returns sum of all updates on position p)
*/

struct segmentTree
{
    int sz;
    vector <int> elements;

    segmentTree(int s)
    {
        sz = s;
        elements.resize(2 * sz);
    }

    void modify(int l, int r, int v)
    {
        for (l += sz, r += sz; l <= r; ++l >>= 1, --r >>= 1)
        {
            if (l & 1) elements[l] += v;
            if (!(r & 1)) elements[r] += v; // Caution!! Might want to min(elements[l], INF), min(elements[r], INF)
        }
    }

    int query(int p)
    {
        int acc = 0;
        for (p += sz; p >= 1; p >>= 1)
            acc += elements[p]; // Cuation!! Same as above
        return acc;
    }
};

int main()
{
    segmentTree st(5);
    st.modify(0, 3, 5), st.modify(3, 4, 3), st.modify(1, 1, 1);
    st.modify(0, 4, -4), st.modify(2, 2, 100);
    // Expected: 1 2 101 4 -1
    for (int i = 0; i < 5; i++)
        cout << st.query(i) << " ";
    cout << '\n';
}
