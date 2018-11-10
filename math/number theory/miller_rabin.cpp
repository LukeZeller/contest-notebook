/* Description: Miller-Rabin primality test
 * Dependency: binary exponentiation
 */

int accuracy = 20;

/* Note: Remember to initialize seed in main */
bool primeTest(int d, int n) 
{ 
    int a = 2 + rand() % (n - 4); 
    int x = binaryPower(a, d, n);   
    if (x == 1  || x == n-1) 
       return true; 
    while (d != n-1) 
    {
        x = (x * x) % n; 
        d *= 2; 
        if (x == 1) return false; 
        if (x == n - 1) return true; 
    } 
    return false; 
}

bool isPrime(int n) 
{ 
    // Corner cases 
    if (n <= 1 || n == 4)  return false; 
    if (n <= 3) return true; 
  
    int d = n - 1; 
    while (d % 2 == 0) d /= 2; 
    for (int i = 0; i < accuracy; i++) if (!primeTest(d, n)) return false;
    return true; 
}
// Driver program 
int main() 
{ 
    int k = 4;  // Number of iterations 
  
    cout << "All primes smaller than 100: \n"; 
    for (int n = 1; n < 100; n++) 
        if (isPrime(n))
          cout << n << " ";
    return 0; 
} 
