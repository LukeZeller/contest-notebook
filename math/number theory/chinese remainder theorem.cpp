/*
* Description: Chinese remainder theorem for solving systems of congruences
* Demo: Finds solution if it exists, otherwise returns {-1, -1}
* Dependency: extended gcd
*/

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
