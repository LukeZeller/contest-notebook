#include <iostream>

using namespace std;

#define ll long long

int mult(int a, int b, int mod)
{
    return (ll) a * b % mod;
}

int binaryPower(int n, int p, int mod)
{
    int acc = 1;
    for (; p; p >>= 1)
    {
        if (p & 1) acc = mult(acc, n, mod);
        n = mult(n, n, mod);
    }
    return acc;
}

int pmodularInverse(int n, int pmod)
{
    return binaryPower(n, pmod - 2, pmod);
}

int main()
{
    //Expected: 2
    cout<<pmodularInverse(5, 3)<<'\n';

    //Expected: 4
    cout<<pmodularInverse(3, 11)<<'\n';

    //Expected: 9765625
    cout<<binaryPower(5, 10, 1000000000)<<'\n';

    return 0;
}
