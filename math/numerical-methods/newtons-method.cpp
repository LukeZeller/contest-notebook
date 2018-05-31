/*
* Description: newtons method
* Demo: finds zeros of function given a starting guess (close to local extrema/far from root is bad) and derivative
        M is maximum number of iterations, eps is tolerance for error.
*/

#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

const int INF = 1231231234;

template <typename Operation, typename Operation2>
double newtonMethod(Operation &f, Operation2 &df, double x0, int M = 1e5, double eps = 1e-6)
{
    double x = x0;
    for (int counter = 0; counter < M; counter++)
    {
        double fx = f(x), dfx = df(x);
        if (abs(dfx) < eps or abs(fx) < eps)
        {
            return x;
        }
        x -= fx / dfx;
    }
    return INF;
}

int main()
{
    auto f = [&](double x) -> double {return cos(x) - x;};
    auto df = [&](double x) -> double {return -sin(x) - 1;};
    //Expected: 0.739085
    cout<<newtonMethod(f, df, 0.0)<<'\n';

    return 0;
}
