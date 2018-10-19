/*
* Description: trie
* Demo: exists() checks if s is in trie, numPrefixes() gives number of distinct prefixes of s in trie
*/

const int alpha = 26; /*PS*/
const int MAXN = 3e6; /*PS*/

struct node
{
    int to[alpha], counts[alpha]; //PS: can use maps instead
    int isEnd = 0;

    node() //PS: remove constructor if using map
    {
        memset(to, -1, sizeof(to));
        memset(counts, 0, sizeof(counts));
    }
};

int mapping(char c){return c - 'a';} /*PS*/
char invmap(int i){return i + 'a';} /*PS*/

struct trie
{
    vector <node> elements;
    int numNodes;

    trie()
    {
        elements.resize(1);
        numNodes = 1;
    }

    int& next(int i, int t){return elements[i].to[t];} //PS: modify if using map
    int& counts(int i, int t){return elements[i].counts[t];} //PS: same as above

    void addString(const string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (next(curr, mc) == -1) elements.emplace_back(), next(curr, mc) = numNodes++;
            counts(curr, mc)++;
            curr = next(curr, mc);
        }
        elements[curr].isEnd++;
    }

    void removeString(const string &s)
    {
        if (!exists(s)) return; //PS: only use if no guarantee that strings are in trie
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            counts(curr, mc)--;
            curr = next(curr, mc);
        }
        elements[curr].isEnd--;
    }

    bool exists(const string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (next(curr, mc) != -1 and counts(curr, mc) > 0) curr = next(curr, mc);
            else return false;
        }
        return elements[curr].isEnd;
    }

    int numPrefixes(const string &s)
    {
        int curr = 0;
        int sol = elements[curr].isEnd ? 1 : 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (next(curr, mc) != -1 and counts(curr, mc) > 0) curr = next(curr, mc);
            else break;
            if (elements[curr].isEnd) sol++;
        }
        return sol;
    }
};

int main()
{
    trie tr;
    tr.addString("hello"), tr.addString("hey"), tr.addString("he"), tr.addString("he");
    //Expected: 0 0 1
    cout<<tr.exists("heyo")<<" "<<tr.exists("h")<<" "<<tr.exists("hey")<<'\n';
    //Expected: 2 0
    cout<<tr.numPrefixes("helloworld")<<" "<<tr.numPrefixes("h")<<'\n';
    tr.removeString("he");
    //Expected: 2
    cout<<tr.numPrefixes("helloworld")<<'\n';
    tr.removeString("he");
    //Expected: 1
    cout<<tr.numPrefixes("helloworld")<<'\n';
}
