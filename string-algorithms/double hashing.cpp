/*
* Description: double hashing for string matching
* Demo: findMatches() gives all instances of targetHash in hashPair
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const int MAXN = 300005;
const int alpha = 37;
const int MOD[2] = {1000000007, 1000000009};

int pAlpha[2][MAXN];
void precompute_hash() //Caution !! Don't forget to call this once at start
{
    for (int t = 0; t < 2; t++)
    {
        pAlpha[t][0] = 1;
        for (int i = 1; i < MAXN; i++)
            pAlpha[t][i] = (ll) alpha * pAlpha[t][i - 1] % MOD[t];
    }
}

struct hasher
{
    int t;
    vector <int> h;

    hasher(int tp) : t(tp) {h.assign(1, 0);}

    int multpow(int v, int p, int t){return (ll) v * pAlpha[t][p] % MOD[t];}
    int mapping(char c){return c - 'a' + 1;} //PS: remember to offset by 1

    int length(){return h.size() - 1;}
    int query(int l, int r){return multpow((h[r + 1] - h[l] + MOD[t]) % MOD[t], MAXN - l - 1, t);}

    void push(char c){h.push_back(h.back() + multpow(mapping(c), h.size(), t)); h.back() %= MOD[t];}
    void pop(){h.pop_back();}

    void init(const string &s)
    {
        *this = hasher(t);
        for (int i = 0; i < s.length(); i++) push(s[i]);
    }
};

struct hashPair
{
    hasher h[2] = {hasher(0), hasher(1)};

    int length(){return h[0].length();}
    pair <int, int> query(int l, int r){return {h[0].query(l, r), h[1].query(l, r)};}
    void push(char c){h[0].push(c), h[1].push(c);} //PS: following functions are just sugar
    void pop(){h[0].pop(), h[1].pop();}
    void init(const string &s){h[0].init(s), h[1].init(s);}

    vector <int> findMatches(hashPair &th)
    {
        vector <int> matches;
        auto target = th.query(0, th.length() - 1);
        for (int i = 0; i + th.length() - 1 < length(); i++)
        {
            auto possible = query(i, i + th.length() - 1);
            if (possible == target) matches.push_back(i);
        }
        return matches;
    }
};

int main()
{
    precompute_hash();

    string s = "hihohihi", t = "hihi";

    hashPair h, th;

    th.init(t);
    for (char c: s) h.push(c);

    //Expected: 4
    for (int i: h.findMatches(th)) cout<<i<<" ";
    cout<<'\n';

    for (int i = 0; i < 4; i++) h.pop();
    //Expected: N/A
    for (int i: h.findMatches(th)) cout<<i<<" ";
    cout<<'\n';

    h.pop(), h.push('i');
    //Expected: 0
    for (int i: h.findMatches(th)) cout<<i<<" ";
    cout<<'\n';
    h.init("hihihihi");
    //Expected: 0 2 4
    for (int i: h.findMatches(th)) cout<<i<<" ";
    cout<<'\n';

    return 0;
}
