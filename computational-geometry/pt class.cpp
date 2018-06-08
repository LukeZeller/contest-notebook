/*
* Description: vector operations
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

const double EPS = 1e-9;

typedef ll ptT; //PS: otherwise long double
struct pt
{
    ptT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
};

int orientation(const pt &o, const pt &a, const pt &b)
{
    auto cp = (b - o) ^ (a - o);
    return cp > 0 ? 1 : (cp < 0 ? -1 : 0); //PS: change > 0 to > EPS and < 0 to < -EPS for doubles
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};
