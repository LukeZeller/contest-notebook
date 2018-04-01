/*
* Description: sparse table
* Demo: range min query
*/

#include <iostream>
#include <vector>

using namespace std;

struct sparseTable
{
    int sz, h = 0;
    vector <vector<int>> table;
    vector <int> lg;

    sparseTable(vector <int> &v)
    {
        sz = v.size(); while (1 << h < sz) h++;
        table.resize(sz, vector<int>(h + 1, -1)), lg.resize(sz + 1);
        build(v);
    }

    void build(vector <int> &v)
    {
        for (int i = 2; i <= sz; i++)
            lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i < sz; i++)
            table[i][0] = v[i];
        for (int j = 1; j <= h; j++)
        {
            for (int i = 0; i + (1 << j) - 1 < sz; i++)
            {
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r)
    {
        int k = lg[r - l + 1];
        return min(table[l][k], table[r - (1 << k) + 1][k]);
    }
};

int main()
{
    int n = 7;
    vector <int> v = {10, 300, 15, 7, -20, 5, -100};
    sparseTable sp(v);

    //Expected: 10 300 15 7 -20 5 -100
    for (int i = 0; i < n; i++) cout<<sp.query(i, i)<<" ";
    cout<<'\n';
    //Expected: 7 -100 -100 -20
    cout<<sp.query(1, 3)<<" "<<sp.query(4, 6)<<" "<<sp.query(0, 6)<<" "<<sp.query(1, 5)<<'\n';

    return 0;
}
