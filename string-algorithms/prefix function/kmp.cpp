/*
* Description: kmp algorithm for string matching
* Demo: kmpAutomata allows online string matching with s, kmpMatch finds match between (larger) text and s
*/

#include <iostream>
#include <vector>

using namespace std;

const int alpha = 26;

struct edge{int to; string str;};
typedef vector <vector<edge>> graph;

vector <int> prefixFunction(string &s)
{
    vector <int> pf(s.length());
    for (int i = 1; i < s.length(); i++)
    {
        int j = pf[i - 1];
        while (j > 0 and s[i] != s[j]) j = pf[j - 1];
        if (s[i] == s[j]) pf[i] = j + 1;
        else pf[i] = 0;
    }
    return pf;
}

int mapping(char c){return c - 'a';}
char invmap(int i){return i + 'a';}

vector <vector<int>> kmpAutomata(string &s)
{
    int n = s.length();
    auto pf = prefixFunction(s);
    vector <vector<int>> automata(n + 1, vector<int>(alpha));
    for (int i = 0; i <= n; i++) for (int c = 0; c < alpha; c++)
    {
        if (i > 0 and invmap(c) != s[i]) automata[i][c] = automata[pf[i - 1]][c];
        else automata[i][c] = i + (invmap(c) == s[i]);
    }
    return automata;
}

vector <int> kmpMatch(string &text, string &s, const vector <int> &pfs)
{
    vector <int> matches;
    for (int i = 0, j = 0; i < text.length(); i++)
    {
        while (j > 0 and text[i] != s[j]) j = pfs[j - 1];
        if (text[i] == s[j] and ++j == s.length())
            matches.push_back(i + 1 - s.length());
    }
    return matches;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s = "helloworld";
    auto automata = kmpAutomata(s);

    string stream = "helloworldhelohellohelloworld";
    //Expected: 0 to 9, 19 to 28
    int state = 0;
    for (int i = 0; i < stream.length(); i++)
    {
        char c = stream[i];
        state = automata[state][mapping(c)];
        if (state == s.length())
            cout<<"Match at : "<<i - s.length() + 1<<" to "<<i<<'\n';
    }

    string s2 = "aaa", t = "aabaabbaaabaaaa";
    //Expected: 7 11 12
    for (int i: kmpMatch(t, s2, prefixFunction(s2))) cout<<i<<" ";
    cout<<'\n';

    return 0;
}
