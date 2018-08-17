/*
*  Description: gcd via the euclidean algorithm
*/

int gcd(int a, int b)
{
    while (b != 0)
    {
        tie(a, b) = make_tuple(b, a % b);
    }
    return a;
}
