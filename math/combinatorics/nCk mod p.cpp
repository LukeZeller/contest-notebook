/*
* Description: Calculate n choose k mod p for prime/square-free p
*     Use choose if n, k < p and p prime, use lucas choose if p prime, use crt choose if p not prime but square free
* Demo: To use crt choose, calculate prime factors of mod (p) ahead of time and pass in as mod_factors
* Dependency: extended gcd, chinese remainder theorem
*/

// assumes a is relatively prime to mod
int modularInverse(int a, int mod)
{
    bezout_coefficients c = extended_gcd(a, mod);
    return c.x < 0 ? c.x + mod : c.x;
}

// only use with prime mod and if n, k < p
ll choose(ll n, ll k, ll mod)
{
    if (k < 0 or k > n)
        return 0;
    ll num = factorial[n];
    ll denom = mult(modularInverse(factorial[k], mod), modularInverse(factorial[n - k], mod), mod);
    return num * denom % mod;
}

// use with prime mod
ll lucas_choose(ll n, ll k, ll p)
{
    int res = 1;
    for(; n; n /= p, k /= p)
        res = mult(res, choose(n % p, k % p, p), p);
    return res;
}

// use with square-free mod, mod_factors must contain all prime factors of mod
ll crt_choose(ll n, ll k, const vector <ll> &mod_factors)
{
    vector <congruence> congruences;
    for (ll p: mod_factors)
        congruences.push_back({lucas_choose(n, k, p), p});
    congruence sol = chinese_remainder_theorem(congruences);
    return sol.residue;
}

int main()
{
    precompute_factorial(MAXN, 30); // calculate factorials mod 30

    // Expected: 1 7 21 5 5 21 7 1
    for (int k = 0; k <= 7; k++)
    {
        cout << crt_choose(7, k, {2, 3, 5}) << " ";
    }
    cout<<'\n';
}
