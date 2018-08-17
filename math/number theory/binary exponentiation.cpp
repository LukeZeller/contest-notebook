/*
* Description: binary exponentiation
*/

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

int main()
{
    //Expected: 9765625
    cout<<binaryPower(5, 10, 1000000000)<<'\n';

    return 0;
}
