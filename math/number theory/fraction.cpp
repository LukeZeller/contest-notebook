/*
* Description: Fraction class
* Demo: closestApproximation(f, M) returns the closest approximation to fraction f with a denominator at most M, can create fraction from double or given numerator/denominator
* Dependency: gcd
*/

template <typename T> T stot(const string &s) // only used in fraction(string) constructor
{
    T res;
    istringstream iss(s);
    iss >> res;
    return res;
}

typedef long long fracT;
struct fraction
{
    fracT num = 0, denom = 1;

    fraction(){}
    fraction(fracT a, fracT b)
    {
        fracT g = gcd(a, b);
        num = a / g, denom = b / g;
        if (denom < 0)
            num = -num, denom = -denom;
    }
    fraction(const string &s, int numRepeating = 0) // if numRepeating != 0, assumes that '.' exists and last numRepeating digits are repeated
    {
        auto it = s.find('.');
        if (it == string::npos)
            *this = fraction(stot<fracT>(s), 1);
        else
        {
            auto whole = s.substr(0, it);
            auto dec = s.substr(it + 1, s.length() - it - numRepeating - 1);
            auto rep = s.substr(s.length() - numRepeating, numRepeating);

            fracT pow10 = 1, nines = 0;
            for (int i = 0; i < dec.length(); i++)
                pow10 *= 10;
            for (int i = 0; i < rep.length(); i++)
                nines = nines * 10 + 9;
            
            *this = (!whole.empty() ? fraction(stot<fracT>(whole), 1) : fraction()) +
                    (!dec.empty() ? fraction(stot<fracT>(dec), pow10) : fraction()) +
                    (!rep.empty() ? fraction(stot<fracT>(rep), nines * pow10) : fraction());
        }
    }
    fraction(ld d)
    {
        double whole, temp;
        d = modf(d, &whole);
        fracT p = 0, q = 1;
        for (int i = 0; i < 18 and d != 0; i++, d = modf(d, &temp))
        {
            d *= 10;
            p = p * 10 + (int) d;
            q *= 10;
        }
        *this =  fraction(p, q) + fraction(whole, 1);
    }

    fraction reciprocal() const {return {denom, num};}
    fraction abs() const {return {std::abs(num), denom};}
    ld eval() const {return (ld) num / denom;}

    fraction operator + (const fraction &o) const {return {num * o.denom + o.num * denom, denom * o.denom};}
    fraction operator - (const fraction &o) const {return {num * o.denom - o.num * denom, denom * o.denom};}
    fraction operator * (const fraction &o) const {return {num * o.num, denom * o.denom};}
    fraction operator / (const fraction &o) const {return {num * o.denom, denom * o.num};}

    fraction operator * (fracT k) const {return {num * k, denom};}
    fraction operator / (fracT k) const {return {num, denom * k};}
    fraction operator + (fracT k) const {return *this + fraction(k, 1);}
    fraction operator - (fracT k) const {return *this - fraction(k, 1);}
};

ostream& operator << (ostream &os, const fraction &f)
{
    return os << f.num << " / " << f.denom;
}

fraction closestApproximation(const fraction &f, long long maxDenom)
{
    fracT p0 = 0, q0 = 1, p1 = 1, q1 = 0, n = f.num, d = f.denom;
    while (d != 0)
    {
        fracT a = n / d, q2 = q0 + a * q1;
        if (q2 > maxDenom)
            break;
        tie(p0, q0, p1, q1, n, d) = make_tuple(p1, q1, p0 + a * p1, q2, d, n - a * d);
    }
    fracT k = (maxDenom - q0) / q1;
    fraction f1(p0 + k * p1, q0 + k * q1);
    fraction f2(p1, q1);
    return abs(f1.eval() - f.eval()) < abs(f2.eval() - f.eval()) ? f1 : f2;
}

int main()
{
    fracT k = 3;
    auto a = fraction(1, 3), b = fraction(3, 4);
    // Expected 13 / 12, -5 / 12, 4 / 9, 1 / 4
    cout << a + b << ", " << a - b << ", " << a / b << ", " << a * b << '\n';
    // Expected: 10 / 3, -8 / 3, 1 / 9, 1 / 1
    cout << a + k << ", " << a - k << ", " << a / k << ", " << a * k << '\n';
    // Expected: 31415.../10000..., 4 / 3, 5 / 12, 0.25
    cout << fraction(3.1415) << ", " << b.reciprocal() << ", " << (a - b).abs() << ", " << (a * b).eval() << '\n';
    // Expected: 0 / 1, 355 / 113
    cout << closestApproximation(fraction(1, 7), 3) << ", " << closestApproximation(fraction(acos(-1)), 113) << '\n';
}
