/*
* Description: Extended euclidean algorithm for finding bezout coefficients
* Demo: extended_gcd(a, b) returns (g, x, y) where g = gcd(a, b) and ax + by = g
*/

struct bezout_coefficients
{
    ll g, x, y;
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
