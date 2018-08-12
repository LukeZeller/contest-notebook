/*
* Description: vector operations
*/

const double EPS = 1e-9;

typedef long double ptT; //PS: otherwise long long
struct pt
{
    ptT x, y;

    bool operator < (const pt &o) const {return make_pair(y, x) < make_pair(o.y, o.x);}
    bool operator == (const pt &o) const {return abs(x - o.x) < EPS and abs(y - o.y) < EPS;}

    pt operator + (const pt &o) const {return {x + o.x, y + o.y};}
    pt operator - (const pt &o) const {return {x - o.x, y - o.y};}
    pt operator * (ptT k) const {return {k * x, k * y};}
    pt operator / (ptT k) const {return {x / k, y / k};}

    ptT operator ^ (const pt &o) const {return x * o.y - y * o.x;}
    ptT operator * (const pt &o) const {return x * o.x + y * o.y;}

    pt rotateCw(double theta) {return {cos(theta) * x + sin(theta) * y, - sin(theta) * x + cos(theta) * y};} // Caution!! Only use with doubles
    pt rotateCcw(double theta) {return {cos(theta) * x - sin(theta) * y, sin(theta) * x + cos(theta) * y};} // Same as above
    pt perpCcw() const {return {-y, x};}
    pt perpCw() const {return {y, -x};}

    ptT norm2() const {return *this * *this;}
    ptT dist2(const pt &o) const {return (*this - o).norm2();}
    pt normalize() const {return *this / sqrt(norm2());} // Caution!! Only use with doubles
};
pt operator * (ptT k, const pt &p){return {k * p.x, k * p.y};}

std::istream& operator >> (istream& is, pt &p) {return is >> p.x >> p.y;}
std::ostream& operator << (ostream& os, const pt &p) {return os << p.x << " " << p.y;}

double angleCcw(const pt &a, const pt &b){return atan2(a ^ b, a * b);}
double angleCcw(const pt &o, const pt &a, const pt &b){return angleCcw(a - o, b - o);}

ptT triArea(const pt &o, const pt &a, const pt &b){return (b - o) ^ (a - o);}
int orientation(const pt &o, const pt &a, const pt &b)
{
    ptT cp = (b - o) ^ (a - o);
    return cp > EPS ? 1 : (cp < -EPS ? -1 : 0); //PS: change between > 0 or > EPS and < 0 or < -EPS for ints/doubles
} //cw: 1, ccw: -1, col: 0

typedef vector <pt> polygon;
int prev(int i, int n, int st = 1){return (i - st + n) % n;}
int next(int i, int n, int st = 1){return (i + st) % n;};
