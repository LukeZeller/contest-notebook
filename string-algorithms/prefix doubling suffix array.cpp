/*
* Description: prefix doubling suffix array & kasai's algorithm for LCP construction
* Demo: ranks maps string to suffix array, ordered maps suffix array to string
*       lcp[i] is lcp of i-th and (i + 1)-th element in suffix array
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct element
{
    pair <int, int> ranking;
    int index;

    bool operator < (const element &o) const
    {
        return make_pair(ranking, index) < make_pair(o.ranking, o.index);
    }
};

struct suffixArray
{
    int sz, h = 0, numBuckets;
    vector <int> ranks, ordered, lcp;
    vector <element> suffix;

    suffixArray(string &s)
    {
        sz = s.length(), getHeight();
        ranks.resize(sz), suffix.resize(sz), ordered.resize(sz), lcp.resize(sz);

        for (int i = 0; i < sz; i++) ranks[i] = mapping(s[i]);
        for (int k = 1, len = 1; k <= h; k++, len <<= 1)
        {
            for (int i = 0; i < sz; i++)
                suffix[i] = {{ranks[i], i + len < sz ? ranks[i + len] : -1}, i};
            sort(suffix.begin(), suffix.end());
            numBuckets = 0;
            for (int i = 0; i < sz; i++)
                ranks[suffix[i].index] = i > 0 and suffix[i].ranking == suffix[i - 1].ranking ? ranks[suffix[i - 1].index] : numBuckets++;
            if (numBuckets == sz) break;
        }
        for (int i = 0; i < sz; i++) ordered[ranks[i]] = i;
        kasaiLCP(s); /*PS*/
    }

    void getHeight(){while (1 << h < sz) h++;}
    int mapping(char c){return c - 'a';} /*PS*/

    void kasaiLCP(string &s) /*PS*/
    {
        for(int i = 0, k = 0; i < sz; i++, k = max(0, k - 1))
        {
            if (ranks[i] == sz - 1) {k = 0; continue;}
            int j = ordered[ranks[i] + 1];
            while(i + k < sz and j + k < sz and s[i + k] == s[j + k]) k++;
            lcp[ranks[i]] = k;
        }
    }
};

int main()
{
    string s = "banana";

    auto sa = suffixArray(s);

    //Expected: 5 3 1 0 4 2
    for (int i = 0; i < s.length(); i++)  cout<<sa.ordered[i]<<" ";
    cout<<'\n';

    //3 2 5 1 4 0
    for (int i = 0; i < s.length(); i++) cout<<sa.ranks[i]<<" ";
    cout<<'\n';

    //1 3 0 0 2 0
    for (int i = 0; i < s.length(); i++) cout<<sa.lcp[i]<<" ";
    cout<<'\n';

    return 0;
}
