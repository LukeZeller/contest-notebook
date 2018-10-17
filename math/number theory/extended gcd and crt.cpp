/*
* Description: Chinese remainder theorem for solving systems of congruences
* Demo: Finds solution if it exists, otherwise returns {-1, -1}
*/

struct bezout_coefficients
{
    ll g, x, y; // x * a + y * b = gcd(a, b)
};

bezout_coefficients extended_gcd(ll a, ll b) // x = A[1] stores modular inverse of a in mod b (assuming gcd(a, b) = 1)
{
    array <ll, 3> A = {0, 1, a}, B = {1, 0, b};
    while (B[2] != 0)
    {
        ll q = A[2] / B[2];
        auto T = B;
        transform(A.begin(), A.end(), B.begin(), B.begin(), [q](ll x, ll y){return x - q * y;});
        A = T;
    }
    return {A[2], A[1], A[0]};
}

struct congruence
{
     ll residue, mod; // mod = -1 used to denote invalid/no solution
};

congruence chinese_remainder_theorem(congruence a, congruence b)
{
    bezout_coefficients c = extended_gcd(a.mod, b.mod);

    if (a.mod == -1 or b.mod == -1 or (a.residue - b.residue) % c.g != 0)
        return {-1, -1};

    ll mod = a.mod / c.g * b.mod; // lcm(a.mod, b.mod)
    ll res = (a.residue - (c.x * (a.residue - b.residue) / c.g % (b.mod / c.g)) * a.mod) % mod;
    return {res < 0 ? res + mod : res, mod};
}

congruence chinese_remainder_theorem(vector <congruence> &v)
{
    congruence res = v[0];
    for (int i = 1; i < v.size(); i++)
        res = chinese_remainder_theorem(res, v[i]);
    return res;
}

int main()
{
    int v = 10010;
    vector <int> mods = {3, 108, 13, 33};
    vector <congruence> congruences;
    for (int i = 0; i < mods.size(); i++)
    {
        congruences.push_back({v % mods[i], mods[i]});
    }
    congruence res = congruences[0];
    for (int i = 1; i < congruences.size(); i++)
    {
        res = chinese_remainder_theorem(res, congruences[i]);
    }
    // Expected: 10010 mod 15444
    cout << res.residue << " mod " << res.mod << endl;
}
