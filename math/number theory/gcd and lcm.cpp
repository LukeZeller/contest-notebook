/*
*  Description: gcd via the euclidean algorithm
*               lcm using following property: lcm(a, b) * gcd(a, b) = a * b
*/

int gcd(int a, int b)
{
    while (b != 0)
        tie(a, b) = make_tuple(b, a % b);
    return a;
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}
