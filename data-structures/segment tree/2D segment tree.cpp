/*
* Description: 2D segment tree
* Demo: rectangle sum query, point assignment update
*/

#include <iostream>
#include <vector>

using namespace std;

struct node /*PS*/
{
    int sum = 0; //PS: remember max -> -INF, min -> +INF, sum -> 0

    void init(int i){sum = i;}
    void modify(int v){sum = v;}

    node combine(const node &o)
    {
        node res;
        res.sum = sum + o.sum;
        return res;
    }
};

struct segmentTree2D
{
    int sz, sz2;
    vector <vector<node>> elements;
    vector <vector<int>> v; //PS: can use defaultValue instead

    segmentTree2D(vector <vector<int>> &ve) //PS: can use segmentTree2D(s1, s2) instead
    {
        v = ve, sz = v.size(), sz2 = v[0].size();
        elements.resize(2 * sz, vector<node>(2 * sz2));
        build(); //PS: Careful!!! Runs in O(N^2)
    }

    void build()
    {
        for (int x = sz; x < 2 * sz; x++)
        {
            for (int y = sz2; y < 2 * sz2; y++)
                elements[x][y].init(v[x - sz][y - sz2]);
            for (int y = sz2 - 1; y >= 1; y--)
                elements[x][y] = elements[x][y << 1].combine(elements[x][y << 1 | 1]);
        }
        for (int x = sz - 1; x >= 1; x--)
        {
            for (int y = sz2; y < 2 * sz2; y++)
                elements[x][y] = elements[x << 1][y].combine(elements[x << 1 | 1][y]);
            for (int y = sz2 - 1; y >= 1; y--)
                elements[x][y] = elements[x][y << 1].combine(elements[x][y << 1 | 1]);
        }
    }

    void modify(int x, int y)
    {
        for (y >>= 1; y >= 1; y >>= 1)
        {
            elements[x][y] = elements[x][y << 1].combine(elements[x][y << 1 | 1]);
        }
    }

    void modify(int x, int y, int v)
    {
        elements[x += sz][y += sz2].modify(v);
        modify(x, y);
        for (x >>= 1; x >= 1; x >>= 1)
        {
            elements[x][y] = elements[x << 1][y].combine(elements[x << 1 | 1][y]);
            modify(x, y);
        }
    }

    node query(int x, int y1, int y2)
    {
        node acc;
        for (y1 += sz2, y2 += sz2; y1 <= y2; ++y1 >>= 1, --y2 >>= 1)
        {
            if (y1 & 1) acc = acc.combine(elements[x][y1]);
            if (!(y2 & 1)) acc = acc.combine(elements[x][y2]);
        }
        return acc;
    }

    int query(int x1, int y1, int x2, int y2)
    {
        node lacc, racc;
        for (x1 += sz, x2 += sz; x1 <= x2; ++x1 >>= 1, --x2 >>= 1)
        {
            if (x1 & 1)
                lacc = lacc.combine(query(x1, y1, y2));
            if (!(x2 & 1))
                racc = query(x2, y1, y2).combine(racc);
        }
        return lacc.combine(racc).sum; /*PS*/
    }
};

int main()
{
    vector <vector<int>> v(5, vector<int>(4));
    for (int i = 0; i < 5; i++) for (int j = 0; j < 4; j++) v[i][j] = i * 4 + j;
    segmentTree2D st(v);

    //Expected: 190
    cout<<st.query(0, 0, 4, 3)<<'\n';

    //Expected: 10 14 18 ... 42 46 ... 58 62 66
    for (int i = 0; i + 1< 5; i++) for (int j = 0; j + 1 < 4; j++)
    {
        cout<<st.query(i, j, i + 1, j + 1)<<" ";
    }
    cout<<'\n';

    st.modify(0, 0, 5), st.modify(0, 3, 1), st.modify(4, 0, 2), st.modify(4, 3, 7);

    //Expected: 5 1 2 1 ... 2 17 18 7
    for (int i = 0; i < 5; i++) for (int j = 0; j < 4; j++)
    {
        cout<<st.query(i, j, i, j)<<" ";
    }
    cout<<'\n';

    //Expected: 167
    cout<<st.query(0, 0, 4, 3)<<'\n';
}
