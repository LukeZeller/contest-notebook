/*
* Description: sqrt decomposition on blocks
* Demo: range increment (non-negative) updates, range max queries
* Usage: set block size to sqrt(N) where N is size of vector v
*        to use default value in constructor, pass in [vector<int>(n, default)] when calling
*/

struct sqrt_block
{
    int delta = 0, mx = -INF; /*PS*/
    vector <pair<int, int>> elements;

    void modifyWhole(int v) {delta += v;} /*PS*/
    void modifyPartial(int l, int r, int v)
    {
        for (auto &elem: elements) if (l <= elem.second and elem.second <= r)
            elem.first += v, mx = max(mx, elem.first); /*PS*/
    }

    int queryWhole() {return mx + delta;} /*PS*/
    int queryPartial(int l, int r)
    {
        int res = -INF; /*PS*/
        for (auto &elem: elements) if (l <= elem.second and elem.second <= r)
            res = max(res, elem.first); /*PS*/
        return res + delta; /*PS*/
    }
};

struct block_decomposition
{
    int sz, bsz, nb;
    vector <sqrt_block> blocks;

    block_decomposition(){}
    block_decomposition(const vector <int> &v, int BLOCK_SIZE) : sz(v.size()), bsz(BLOCK_SIZE), nb(sz / BLOCK_SIZE + 1), blocks(nb)
    {
        for (int i = 0; i < v.size(); i++)
            blocks[i / bsz].elements.push_back({v[i], i});
    }

    int overlap(int i, int ql, int qr)
    {
        int lb = i * bsz, rb = (i + 1) * bsz - 1;
        if (ql <= lb and qr >= rb) return 2;
        else if (ql > rb or qr < lb) return 0;
        else return 1;
    } // 2: query covers block, 1: query overlaps block, 0: no overlap

    void modify(int l, int r, int v)
    {
        for (int i = 0; i < nb; i++)
        {
            auto o = overlap(i, l, r);
            if (o == 2)
                blocks[i].modifyWhole(v);
            else if (o == 1)
                blocks[i].modifyPartial(l, r, v);
        }
    }

    int query(int l, int r)
    {
        int acc = -INF; // PS: initialization changes depending on max/min/+
        for (int i = 0; i < nb; i++)
        {
            auto o = overlap(i, l, r);
            if (o == 2)
                acc = max(acc, blocks[i].queryWhole()); // PS: might be + or min() instead of max()
            else if (o == 1)
                acc = max(acc, blocks[i].queryPartial(l, r)); // PS: same as above
        }
        return acc;
    }
};
