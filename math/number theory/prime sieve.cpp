/*
* Description: sieve of eranthoses for prime number detection
* Demo: isPrime() checks if n is prime, factorize() returns list of (factor, power) pairs
*/

const int MAXN = 1000000000;

vector <bool> prm;
vector <int> primes;
void sieve(int n)
{
    int sq = sqrt(n) + 100;
    prm.resize(sq, true);
    for (int i = 2; i < sq; i++)
    {
        if (!prm[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j < sq; j += i)
            prm[j] = false;
    }
}

bool isPrime(int n)
{
    if (n < prm.size()) return prm[n];
    for (int p: primes)
    {
        if (n % p == 0) 
            return false;
    }
    return true;
}

vector <pair<int, int>> factorize(int n)
{
    vector <pair<int, int>> factors;
    for (int p: primes)
    {
        if (n % p == 0) factors.push_back({p, 0});
        while (n % p == 0)
            n /= p, factors.back().second++;
    }
    if (n != 1) factors.push_back({n, 1});
    return factors;
}

int main()
{
    sieve(MAXN);

    //Expected: 1 1 1 0 0
    cout<<isPrime(3)<<" "<<isPrime(1000000007)<<" "<<isPrime(37)<<" "<<isPrime(103793)<<" "<<isPrime(6)<<'\n';

    auto factors = factorize(532901232);
    //Expected: (2, 4) (3, 2) (37, 1) (100019, 1)
    for (auto elem: factors) cout<<"("<<elem.first<<", "<<elem.second<<") ";
    cout<<'\n';
}
