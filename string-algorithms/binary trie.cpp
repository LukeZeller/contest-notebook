/*
* Description: binary trie
* Demo: findMinXorMatch -> finds min xor pairing for n with integers in trie
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int alpha = 2; /*PS*/
const int MAXL = 31; /*PS*/
const int MAXN = 300000 * MAXL + 5; /*PS*/

struct node
{
    int to[alpha], counts[alpha]; //PS: can use maps instead

    node() //PS: remove constructor if using map
    {
        memset(to, -1, sizeof(to));
        memset(counts, 0, sizeof(counts));
    }
};

struct trie
{
    vector <node> elements;
    int numNodes;

    trie() //Note: requires MAXN (number of nodes) and MAXL (max number of binary digits for integers)
    {
        elements.resize(MAXN);
        numNodes = 1;
    }

    int& next(int i, int t){return elements[i].to[t];} //PS: modify if using map
    int& counts(int i, int t){return elements[i].counts[t];} //PS: same as above

    void addInt(int n)
    {
        int curr = 0;
        for (int i = MAXL - 1; i >= 0; i--)
        {
            bool mc = n & (1 << i);
            if (next(curr, mc) == -1) next(curr, mc) = numNodes++;
            counts(curr, mc)++;
            curr = next(curr, mc);
        }
    }

    void removeInt(int n)
    {
        int curr = 0;
        for (int i = MAXL - 1; i >= 0; i--)
        {
            bool mc = n & (1 << i);
            counts(curr, mc)--;
            curr = next(curr, mc);
        }
    }

    int findMinXorMatch(int n)
    {
        int sol = 0;
        int curr = 0;
        for (int i = MAXL - 1; i >= 0; i--)
        {
            bool mc = n & (1 << i), branch;
            if (next(curr, mc) != -1 and counts(curr, mc) > 0) branch = mc;//PS: check (1 - mc) case first for max match
            else branch = 1 - mc;
            curr = next(curr, branch);
            sol += branch * (1 << i);
        }
        removeInt(sol); //PS: remove if allowed to reuse matched number
        return sol;
    }
};

int main()
{
    trie tr;

    tr.addInt(8), tr.addInt(16), tr.addInt(2);

    //Expected: 16 2 8
    for (int i = 0; i < 3; i++) cout<<tr.findMinXorMatch(16)<<" ";
    cout<<'\n';

    return 0;
}
