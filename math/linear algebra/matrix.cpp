/*
* Description: matrix operations
* Demo: multiplication and fast exponentiation (more to be added)
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const int MOD = 1000000007; /*PS*/

typedef int matT; /*PS*/
typedef ll matLT; /*PS*/
struct matrix : vector <vector<matT>>
{
    matrix(int h, int w, matT v){resize(h, vector<matT>(w, v));}
    matrix(int h, int w) : matrix(h, w, 0) {}

    int height() const {return (*this).size();}
    int width() const {return (*this)[0].size();}

    int mult(matT a, matT b){return (matLT) a * b % MOD;} //PS: remove mod if using doubles

    matrix operator * (const matrix &o)
    {
        matrix c(height(), o.width());
        for (int i = 0; i < c.height(); i++)
        {
            for (int j = 0; j < c.width(); j++)
            {
                matT sum = 0;
                for (int k = 0; k < width(); k++)
                    sum = (sum + mult((*this)[i][k], o[k][j])) % MOD;
                c[i][j] = sum;
            }
        }
        return c;
    }

    matrix operator ^ (ll p)
    {
        matrix acc(height(), width()), res = *this;
        for (int i = 0; i < width(); i++) acc[i][i] = 1;
        for (; p; p >>= 1)
        {
            if (p & 1) acc = acc * res;
            res = res * res;
        }
        return acc;
    }
};

int main()
{
    int n = 4;
    matrix m(n, n);
    m[0][0] = 2, m[0][3] = 1, m[3][0] = 3, m[3][3] = 5;
    m = m ^ 10;
    //ExpecteD:  7327852  ... 9260657 ... 27781971 ... 35109823
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cout<<m[i][j]<<" ";

    return 0;
}
