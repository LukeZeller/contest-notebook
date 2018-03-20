/*
* Description: aho-corasick automata for matching text queries with pattern set
* Demo: printAllMatches() outputs all pattern instances (with repetition) and returns first instance of a pattern
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

const int MAXN = 100001; /*PS*/

struct node
{
    map <int, int> to;
    int prefixLink = -1, matchLink = -1, len = 0;
    bool isEnd = false;
};

struct ahoCorasick
{
    int numNodes;
    vector <node> elements;

    ahoCorasick()
    {
        numNodes = 1;
        elements.resize(MAXN);
    }

    int mapping(char c){return c + 128;} /*PS*/

    void addWord(string &s)
    {
        int curr = 0;
        for (char c: s)
        {
            int mc = mapping(c);
            if (next(curr, mc) == -1)
            {
                elements[curr].to[mc] = numNodes++;
                elements[next(curr, mc)].len = elements[curr].len + 1;
            }
            curr = next(curr, mc);
        }
        elements[curr].isEnd = true;
    }

    int next(int i, int t){return elements[i].to.count(t) ? elements[i].to[t] : -1;}

    void build()
    {
        elements[0].prefixLink = 0;
        buildLinks();
    }

    void buildLinks()
    {
        queue <int> q;
        q.push(0);

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            int j = elements[curr].prefixLink;
            elements[curr].matchLink = elements[j].isEnd ? j : elements[j].matchLink;
            for (auto &elem: elements[curr].to)
            {
                int mc = elem.first;

                while (j > 0 and next(j, mc) == -1) j = elements[j].prefixLink;
                if (curr != 0 and next(j, mc) != -1) elements[next(curr, mc)].prefixLink = next(j, mc);
                else elements[next(curr, mc)].prefixLink = 0;

                q.push(next(curr, mc));
            }
        }
    }

    const int INF = 1231231234; //PS: not needed if finding arbitrary/all match(es)
    int printAllMatches(const string &s)
    {
        int first = INF;
        for (int i = 0, j = 0; i < s.length(); i++)
        {
            int mc = mapping(s[i]);

            while (j > 0 and next(j, mc) == -1) j = elements[j].prefixLink;
            if (next(j, mc) != -1) j = next(j, mc);
            else j = 0;

            for (int k = j; k != -1; k = elements[k].matchLink) if (elements[k].isEnd)
            {
                cout<<s.substr(i - elements[k].len + 1, elements[k].len)<<" ";
                first = min(first, i - elements[k].len + 1);
            }
        }
        return first;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector <string> patterns = {"hello", "world", "hi", "he", "orld"};

    ahoCorasick ac;
    for (string s: patterns) ac.addWord(s);
    ac.build();

    //Expected: he hi he hello
    ac.printAllMatches("heyworlhihello");
    cout<<'\n';

    //Expected: world orld
    int first = ac.printAllMatches("sworld");
    cout<<'\n';
    //Expected: 1
    cout<<first<<'\n';

    return 0;
}
