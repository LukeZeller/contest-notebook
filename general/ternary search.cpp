/*
* Description: ternary search to find min/max of function in [l, r] interval
*               assumes function is unimodal
* Demo: finds min of y = x^2 function
*/

const double EPS = 1e-6; /*PS*/

double f(double t)
{
    return t * t;
}

double ternary_search(double l, double r)
{
    while (r - l > EPS)
    {
        double lt = l + (r - l) / 3;
        double rt = r - (r - l) / 3;
        if (f(lt) > f(rt)) //PS: change to < if finding maximum of function
            l = lt;
        else
            r = rt;
    }
    return l;
}

int main()
{
    // Expected: ~0
    cout << ternary_search(-5, 5) << '\n';
    // Expected: ~3
    cout << ternary_search(3, 10000) << '\n';
}
