/*
* Description: Prime modular inverse
* Dependency: Binary exponentiation
*/

int pmodularInverse(int n, int pmod)
{
    return binaryPower(n, pmod - 2, pmod);
}

int main()
{
  //Expected: 2
  cout<<pmodularInverse(5, 3)<<'\n';

  //Expected: 4
  cout<<pmodularInverse(3, 11)<<'\n';
}
