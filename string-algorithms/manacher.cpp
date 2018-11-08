/*
* Description: Manacher's algorithm for longest palindromic substring
* Demo: returns pal[e][i] = # of palindromes with center-i and even-length iff e is true / odd-length iff e is false
* Example: "c b a a b d d b" for even length palindromes
*           0 0 0 2 0 0 2 0
*/

array <vector <int>, 2> manacher(const string &s)
{
    int n = s.length();
    array <vector <int>, 2> pal;
    for (int even = 0; even < 2; even++)
    {
        pal[even].resize(n);
        for (int i = 0, l = 0, r = -1; i < n; i++)
        {
            int k = (i > r) ? !even : min(pal[even][l + r - i + even], r - i + even);
            while (0 <= i - k - even and i + k < n and s[i - k - even] == s[i + k])
                k++;
            pal[even][i] = k--;
            if (i + k > r)
                l = i - k - even, r = i + k;
        }
    }
    return pal;
}

pair <int, int> longestPalindromeSubstring(const string &s)
{
    auto pal = manacher(s);
    int len = s.length();
    pair <int, int> best = {0, 0};
    for (int even = 0; even < 2; even++)
    {
        for (int i = 0; i < len; i++) if (pal[even][i])
        {
            int l = i - pal[even][i] + !even, r = i + pal[even][i] - 1;
            if (r - l + 1 > best.second - best.first + 1)
                best = {l, r};
        }
    }
    return best;
}

void printAllPalindromes(const string &s, int minLength)
{
    auto pal = manacher(s);
    int len = s.length();
    for (int even = 0; even < 2; even++)
    {
        for (int i = 0; i < len; i++) if (pal[even][i])
        {
            int l = i - pal[even][i] + !even, r = i + pal[even][i] - 1;
            for (int step = 0; l + step + minLength - 1 <= r - step; step++)
            {
                int curr_l = l + step, curr_r = r - step;
                cout << s.substr(curr_l, curr_r - curr_l + 1) << '\n';
            }
        }
    }
}

int main()
{
    // Expected: rotor oto kayak aya
    printAllPalindromes("rotorkayak", 3);
    // Expected: 0 4 6 11
    auto lps = longestPalindromeSubstring("rotorkayak"), lps2 = longestPalindromeSubstring("rotorkayaaya");
    cout << lps.first << " " << lps.second << " " << lps2.first << " " << lps2.second << endl;
    // Expected: 0 0 0 2 0 0 2 0
    auto temp = manacher("cbaabddb");
    for (int i: temp[1])
        cout << i << " ";
    cout << '\n';
}
