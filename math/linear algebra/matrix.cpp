/*
* Description: matrix operations
* Demo: multiplication and fast exponentiation (more to be added)
*/

const int MOD = 1000000007; /*PS*/

typedef int matT; /*PS*/
struct matrix : vector<vector<matT>>
{
    matrix(int r, int c, int v = 0){resize(r, vector<matT>(c, v));}
};

matrix operator * (const matrix &a, const matrix &b)
{
    matrix c(a.size(), b[0].size());
    for (int i = 0; i < a.size(); ++i)
        for (int k = 0; k < b.size(); ++k)
            for (int j = 0; j < b[0].size(); ++j)
                c[i][j] = (c[i][j] + (ll) a[i][k] * b[k][j]) % MOD; //PS: remove MOD and (ll) typecast if using doubles
    return c;
}

matrix operator ^ (const matrix &a, ll p)
{
    matrix acc(a.size(), a.size()), res = a;
    for (int i = 0; i < a.size(); i++) acc[i][i] = 1;
    for (; p; p >>= 1)
    {
        if (p & 1) acc = acc * res;
        res = res * res;
    }
    return acc;
}

int main()
{
    int n = 4;
    matrix m(n, n);
    m[0][0] = 2, m[0][3] = 1, m[3][0] = 3, m[3][3] = 5;
    m = m ^ 10;
    //Expected:  7327852  ... 9260657 ... 27781971 ... 35109823
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cout<<m[i][j]<<" ";
}
