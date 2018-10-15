/*
* Description: Sieve for computing euler's totient function
*              phi[i] = # of numbers in range 1 .. i - 1 inclusive that are relatively prime to i
*/

vector <int> primes, phi;
vector <bool> prm;
void totientSieve(int n)
{
    prm.resize(n + 1, true);
    phi.resize(n + 1);
    for (int i = 2; i <= n; i++)
    {
        if (prm[i])
        {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int prime: primes)
        {
            if ((ll) i * prime > n)
                break;

            prm[i * prime] = false;
            if (i % prime == 0)
            {
                phi[i * prime] = phi[i] * prime;
                break;
            }
            else
                phi[i * prime] = phi[i] * phi[prime];
        }
    }
}
