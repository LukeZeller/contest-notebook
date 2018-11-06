/*
* Description: Misc functions relating to palindromes
* Demo: findPalindromes(len, min, max) returns len-length palindromes (increasing order) w/ all digits between min and max inclusive
*       isPalindrome(s) returns true if vector/istring/etc is a palindrome
*/

typedef basic_string<int> istring;

template <class T> bool isPalindrome(const T &s)
{
    return s == T(s.rbegin(), s.rend());
}

void generatePalindromes(istring &s, vector <istring> &palindrome, int minDigit, int maxDigit, int len)
{
    if (2 * s.length() > len) assert(false);
    else if (2 * s.length() == len)
    {
        istring rev(s.rbegin(), s.rend());
        palindrome.push_back(s + rev);
    }
    else if(2 * s.length() + 1 == len)
    {
        istring rev(s.rbegin(), s.rend());
        for (int i = minDigit; i <= maxDigit; i++)
            palindrome.push_back(s + i + rev);
    }
    else
    {
        for (int i = minDigit; i <= maxDigit; i++) if (!s.empty() or i > 0)  // PS: if-condition ensures no leading-zeros
        {
            s += i;
            generatePalindromes(s, palindrome, minDigit, maxDigit, len);
            s.pop_back();
        }
    }
}

vector <istring> findPalindromes(int len, int minDigit, int maxDigit)
{
    vector <istring> res;
    istring init;
    generatePalindromes(init, res, minDigit, maxDigit, len);
    return res;
}
