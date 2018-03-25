//trie, combinatorics (counting/permutations), modular inverse
//https://naipc18.kattis.com/problems/prefixfreecode
//2018 NAIPC

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define ll long long

const int alpha = 26;
const int MAXN = 1e6 + 5000;
const int MOD = 1000000007;

int mult(int a, int b)
{
    return (ll) a * b % MOD;
}

int binaryPower(int n, int p)
{
    int acc = 1;
    for (; p; p >>= 1)
    {
        if (p & 1) acc = mult(acc, n);
        n = mult(n, n);
    }
    return acc;
}

int pmodularInverse(int n)
{
    return binaryPower(n, MOD - 2);
}

struct node
{
    int to[alpha], counts[alpha];
    int isEnd = 0;

    node()
    {
        memset(to, -1, sizeof(to));
        memset(counts, 0, sizeof(counts));
    }
};

int mapping(char c){return c - 'a';}
char invmap(int i){return i + 'a';}

struct trie
{
    vector <node> elements;
    int numNodes, numWords, ways;

    trie(int n, int m)
    {
        elements.resize(MAXN);
        numNodes = 1, numWords = 0, ways = 1;
        for (int i = n - m + 1; i <= n; i++)
        {
            ways = mult(ways, i);
        }
    }

    int& next(int i, int t){return elements[i].to[t];}
    int& counts(int i, int t){return elements[i].counts[t];}

    void addString(const string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (next(curr, mc) == -1) next(curr, mc) = numNodes++;
            counts(curr, mc)++;
            curr = next(curr, mc);
        }
        elements[curr].isEnd++;
        numWords++;
    }

    void removeString(const string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            counts(curr, mc)--;
            curr = next(curr, mc);
        }
        elements[curr].isEnd--;
        numWords--;
    }

    int findString(string &s)
    {
        int sol = 0;
        int cost = 0, curr = 0;
        string currString = "";
        for (char c: s)
        {
            int mc = mapping(c);
            for (int i = 0; i < mc; i++)
                cost = (cost + counts(curr, i)) % MOD;
            curr = next(curr, mc);
            currString += c;
            if (elements[curr].isEnd)
            {
                ways = mult(ways, pmodularInverse(numWords));
                sol = (sol + mult(cost, ways)) % MOD;

                removeString(currString);
                curr = 0, cost = 0, currString = "";
            }
        }
        return sol;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;

    trie tr(n, m);
    for (int i = 0; i < n; i++)
    {
        string s;
        cin>>s;
        tr.addString(s);
    }
    string t;
    cin>>t;

    cout<<(tr.findString(t) + 1) % MOD<<'\n';

    return 0;
}
