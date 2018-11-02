/*
* Description: adaptive simpson's method for integration
* Demo: For "Function f", integrate()/fast_integrate() accept a lambda function ld -> ld or a struct/class with "operator () (ld x) -> ld" defined
*       optional eps parameter to either integrate()/fast_integrate() allows for making integration error different from global EPS
*       also includes polynomial functor
* Usage: Exact for polynomials of degree 3 or less, but not good w/ discontinuities/misbehaved higher derivatives
*/

/* Slow Simpson (recalculates function values instead of saving them, fine in most cases) */
template <class Function>
ld simpson(Function f, ld a, ld b)
{
    return (f(a) + 4 * f((a + b) / 2.0) + f(b)) * (b - a) / 6.0;
}

template <class Function>
ld integrate(Function f, ld a, ld b, ld eps = EPS)
{
    ld m = (a + b) / 2.0;
    ld l = simpson(f, a, m), r = simpson(f, m, b), total = simpson(f, a, b);
    if (abs(l + r - total) < eps) return total;
    return integrate(f, a, m, eps) + integrate(f, m, b, eps);
}

/* Optimized Simpson (use for computationally intensive tasks, ex. area of circle union) */
inline ld fast_simpson(ld fl, ld fr, ld fm, ld l, ld r) { return (fl + fr + 4.0 * fm) *(r - l) / 6.0; }

template <class Function>
ld fast_rsimpson(Function f, ld slr, ld fl, ld fr, ld fm, ld l, ld r, ld eps)
{
	ld m = (l + r) / 2.0;
	auto fml = f((l + m) / 2.0), fmr = f((m + r) / 2.0);
	auto slm = fast_simpson(fl, fm, fml, l, m), smr = fast_simpson(fm, fr, fmr, m, r);
	if(abs(slr - slm - smr) < EPS) return slm + smr;
	return fast_rsimpson(f, slm, fl, fm, fml, l, m, eps) + fast_rsimpson(f, smr, fm, fr, fmr, m, r, eps);
}

template <class Function>
ld fast_integrate(Function f, ld l, ld r, ld eps = EPS)
{
	auto m = (l + r) / 2.0;
	auto fl = f(l), fr = f(r), fm = f(m);
	return fast_rsimpson(f, fast_simpson(fl, fr, fm, l, r), fl, fr, fm, l, r, eps);
}

struct polynomial
{
    int sz;
    vector <ld> poly;

    polynomial(int s): sz(s), poly(sz) {}

    ld operator()(ld x) // y-value of polynomial at given x-coordinate
    {
        ld res = 0.0, xpow = 1.0;
        for (int i = 0; i < sz; i++)
        {
            res += poly[i] * xpow;
            xpow *= x;
        }
        return res;
    }
};

int main()
{
    polynomial p(3);
    p.poly = {1, 2, 1};
    // Expected: 69.333333 69.333333
    cout << fixed << setprecision(6) << fast_integrate(p, 1, 5) << " " << fast_integrate(p, 1, 5, 1e-2) << '\n';

    auto upper_semicircle = [](ld x){return (x < 1.0 or x > 3.0) ? 0.0 : 3 + sqrt(-1 * x * x + 4 * x - 3);}; // radius-1 upper semicircle with center (2, 3)
    auto lower_semicircle = [](ld x){return (x < 1.0 or x > 3.0) ? 0.0 : 3 - sqrt(-1 * x * x + 4 * x - 3);}; // radius-1 lower semicircle with center (2, 3)
    // Expected: 7.570796 4.429204
    cout << fast_integrate(upper_semicircle, 1, 3) << " " << integrate(lower_semicircle, 1, 3) << '\n';

    auto x3 = [](ld x){return x * x * x;};
    // Expected: -39843.750000
    cout << integrate(x3, -20, 5) << '\n';
}
