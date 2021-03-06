/*
* Description: Misc. number theory related theorems
* Demo: Fermat's little theorem, Euler's theorem, Goldbach Conjecture, Zeckendorf Theorem, Euclid's formula
*/

Fermat's little theorem: a^p = a (mod p) if p is prime
Corollary: if a is not divisible by prime p => a^(p - 1) = 1 (mod p)

Euler's theorem: a^(phi n) = 1 (mod n) if gcd(a, n) = 1

Goldbach's (strong) Conjecture: Every even integer > 2 is the sum of two primes
Goldbach's (weak) Conjecture: Every odd integer > 5 is the sum of 3 primes (not necessarily distinct)

Zeckendorf's theorem: every positive integer is represented unique as sum of 
                      one or more distinct fibonacci numbers s.t two consecutive fib. numbers aren't both used
                      This representation can be found by greedily picking the largest fib. number possible repeatedly
                      
Euclid's formula: all primitive pythagorean triples can be generated by 
                  [a = m^2 - n^2], [b = 2 * m * n], [c = m^2 + n^2] if n or m is even, and gcd(n, m) = 1
                  to generate non-primitive triples, use some constant k to scale all three of (a, b, c)
