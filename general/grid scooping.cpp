/*
* Description: Find # of fixed-size boxes that cover a space in a grid
* Demo: numCover(x, y, r, n) returns # of r x r boxes that cover position (x, y) on a n x m grid
*/

ll numCover(ll x, ll y, ll r, ll n, ll m)
{
    return (min(x, n - r) - max(x - r + 1, 0LL) + 1) * (min(y, m - r) - max(y - r + 1, 0LL) + 1);
}
