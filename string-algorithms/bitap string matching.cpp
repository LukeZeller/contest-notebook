/*
* Description: bitap algorithm for fast string matching
* Demo: bitapMatch finds matches of s in text in range, getMask must be called first
* Runtime: O(N^2) (divide by 32 b/c bitset is fast)
*/

#include <iostream>
#include <vector>
#include <bitset>
#include <array>

using namespace std;

const int MAXN = 100001;
const int alpha = 26;

typedef array<bitset<MAXN>, alpha> mask;

int mapping(char c){return c - 'a';} /*PS*/
char invmap(int i){return i + 'a';} /*PS*/

mask getMask(string &text)
{
    mask mk;
    for (int i = 0; i < text.length(); i++)
        mk[mapping(text[i])][i] = 1;
    return mk;
}

void modifyText(mask &mk, string &text, int p, char c)
{
    mk[mapping(text[p])][p] = 0;
    mk[mapping(c)][p] = 1;
    text[p] = c;
}

int bitapMatch(mask &mk, string &s, int l, int r)
{
    if (l + s.length() - 1 > r) return 0;
    bitset <MAXN> matches = bitset<MAXN>().set();
    for (int i = 0; i < s.length(); i++)
    {
        matches &= mk[s[i] - 'a'] >> i;
        if (matches.none()) return 0;
    }
    return (matches >> l).count() - (matches >> r - s.length() + 2).count();
}

int main()
{
    string t = "helloworldhello";
    mask mk = getMask(t);

    string s = "ello";
    //Expected: 2
    cout<<bitapMatch(mk, s, 0, t.length() - 1)<<'\n';

    s = "elle";
    modifyText(mk, t, 4, 'e');
    //Expected: 1
    cout<<bitapMatch(mk, s, 0, t.length() - 1)<<'\n';
    //Expected: 0
    cout<<bitapMatch(mk, s, 2, t.length() - 1)<<'\n';

    return 0;
}
