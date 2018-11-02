/*
* Description: Sqrt decomposition on sorted blocks
* Demo: Supports window range queries (# of elements in [ql, qr] subarray with values in range [lo, hi]), and point assignment updates (set a[p] = v)
*       setPosition(p, v, a, block_decomp) finds change in # of inversions after setting a[p] = v
* Usage: Initialize block size to BLOCK if input size matches comment below, otherwise set to (sqrt(n) + 5)
*/

const int BLOCK = 800; // ~ 3.7s for N = 2 * 10^5, Q = 10^5
struct sqrt_block
{
    vector <pair<int, int>> elements;

    void modifyPartial(int p, int v)
    {
        for (auto &elem: elements) if (elem.second == p)
            elem.first = v;
        sort(elements.begin(), elements.end());
    }

    int queryWhole(int lo, int hi)
    {
        return lower_bound(elements.begin(), elements.end(), make_pair(hi + 1, -INF)) -
               lower_bound(elements.begin(), elements.end(), make_pair(lo, -INF));
    }

    int queryPartial(int l, int r, int lo, int hi)
    {
        int res = 0;
        for (auto &elem: elements) if (l <= elem.second and elem.second <= r)
            res += (lo <= elem.first and elem.first <= hi);
        return res;
    }
};

struct block_decomposition
{
    int sz, bsz, nb;
    vector <sqrt_block> blocks;

    block_decomposition(const vector <int> &v, int BLOCK_SIZE) : sz(v.size()), bsz(BLOCK_SIZE), nb(sz / BLOCK_SIZE + 1), blocks(nb)
    {
        for (int i = 0; i < v.size(); i++)
            blocks[i / bsz].elements.push_back({v[i], i});
        for (auto &b: blocks)
            sort(b.elements.begin(), b.elements.end());
    }

    int overlap(int i, int ql, int qr)
    {
        int lb = i * bsz, rb = (i + 1) * bsz - 1;
        if (ql <= lb and qr >= rb) return 2;
        else if (ql > rb or qr < lb) return 0;
        else return 1;
    } // 2: query covers block, 1: query overlaps block, 0: no overlap

    void modify(int p, int v)
    {
        for (int i = 0; i < nb; i++) if (overlap(i, p, p) != 0)
            blocks[i].modifyPartial(p, v);
    }

    int query(int ql, int qr, int lo, int hi)
    {
        int acc = 0;
        for (int i = 0; i < nb; i++)
        {
            auto o = overlap(i, ql, qr);
            if (o == 2)
                acc += blocks[i].queryWhole(lo, hi);
            else if (o == 1)
                acc += blocks[i].queryPartial(ql, qr, lo, hi);
        }
        return acc;
    }
};

int setPosition(int p, int v, vector <int> &a, block_decomposition &bd)
{
    int n = a.size();
    ll diff = 0;
    if (a[p] == v)
        return 0;
    if (p - 1 >= 0)
    {
        if (v < a[p])
            diff += bd.query(0, p - 1, v + 1, a[p]);
        else
            diff -= bd.query(0, p - 1, a[p] + 1, v);
    }
    if (p + 1 < n)
    {
        if (a[p] < v)
            diff += bd.query(p + 1, n - 1, a[p], v - 1);
        else
            diff -= bd.query(p + 1, n - 1, v, a[p] - 1);
    }
    bd.modify(p, v);
    a[p] = v;
    return diff;
}

int main()
{
    int n = 5;
    vector <int> a(n);
    for (int i = 0; i < n; i++) a[i] = i;
    block_decomposition bd(a, sqrt(n));
    // Expected: 4 0
    cout << setPosition(0, 6, a, bd) << " " << setPosition(0, 6, a, bd) << '\n';
    // Expected: 1 2 4
    cout << bd.query(0, 2, 5, 100) << " " << bd.query(0, 2, 0, 4) << " " << bd.query(0, n - 1, 0, 4) << '\n';
}
