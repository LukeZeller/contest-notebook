/*
* Description: convex polygon base code
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long

typedef ll ptT; //PS: otherwise long double

const double EPS = 1e-9;

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

int sgn(ptT i) {return (i > -EPS) - (i < EPS);}
int orientation(pt &o, pt &a, pt &b) {return sgn((b - o) ^ (a - o));} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};
