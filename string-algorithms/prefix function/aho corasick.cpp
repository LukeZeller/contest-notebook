/*
* Description: aho-corasick automata for matching text queries with pattern set
* Demo: nextState takes state and transition and returns resulting state, isTerminal returns true iff the state corresponds to the end of a string (can be memoized)
        getStr() prints the string associated with a state, printAllMatches prints all strings in automata that are contained in input string
*/

const int alpha = 256; /*PS*/
struct node
{
    map <int, int> next; // PS: next/go can be any combination of map/array
    array <int, alpha> go;
    int terminalIdx = -1, prefixLink = -1, matchLink = -1; // iff terminalIdx != -1, it denotes the index of the string ending at this node
    int par, pch;

    node(int p = -1, int ch = -1) : par(p), pch(ch) {fill(go.begin(), go.end(), -1);} /*PS*/
};

struct ahoCorasick
{
    int sz;
    vector <node> elements;

    ahoCorasick(){sz = 1, elements.resize(1);}

    int mapping(unsigned char c){return c;}
    unsigned char invmapping(int i){return i;}

    int next(int v, int t){return elements[v].next.count(t) ? elements[v].next[t] : -1;}
    int go(int v, int t){return elements[v].go[t];}

    void addWord(string const &s, int idx = -2)
    {
        int v = 0;
        for (char ch : s)
        {
            int c = mapping(ch);
            if (next(v, c) == -1)
            {
                elements[v].next[c] = sz++;
                elements.emplace_back(v, c);
            }
            v = next(v, c);
        }
        elements[v].terminalIdx = idx;
    }

    int getLink(int v)
    {
        if (elements[v].prefixLink == -1)
        {
            elements[v].prefixLink = elements[v].par <= 0 ? 0 : nextState(getLink(elements[v].par), elements[v].pch);
            getLink(elements[v].prefixLink);

            int link = elements[v].prefixLink;
            elements[v].matchLink = (elements[link].terminalIdx != -1) ? link: elements[link].matchLink;
        }
        return elements[v].prefixLink;
    }

    int nextState(int v, int c)
    {
        if (go(v, c) == -1)
        {
            if (next(v, c) != -1)
                elements[v].go[c] = next(v, c);
            else
                elements[v].go[c] = v == 0 ? 0 : nextState(getLink(v), c);
        }
        return go(v, c);
    }

    bool isTerminal(int v)
    {
        getLink(v);
        return elements[v].terminalIdx != -1 or (elements[v].matchLink != -1 and isTerminal(elements[v].matchLink));
    }

    string getStr(int v)
    {
        string res = "";
        for (int j = v; elements[j].par != -1; j = elements[j].par)
            res += invmapping(elements[j].pch);
        reverse(res.begin(), res.end());
        return res;
    }

    int printAllMatches(const string &s)
    {
        int cnt = 0;
        for (int i = 0, state = 0; i < s.length(); i++)
        {
            state = nextState(state, mapping(s[i]));
            getLink(state);
            for (int j = state; j != -1; j = elements[j].matchLink)
                if (elements[j].terminalIdx != -1)
                {
                    cout << getStr(j) << " ";
                    cnt++;
                }
        }
        return cnt;
    }
};

int main()
{
    vector <string> patterns = {"hello", "world", "hi", "he", "orld"};

    ahoCorasick ac;
    for (string s: patterns) ac.addWord(s);

    //Expected: he hi he hello
    ac.printAllMatches("heyworlhihello");
    cout<<'\n';

    //Expected: world orld 2
    int numMatch = ac.printAllMatches("sworld");
    cout<<numMatch << '\n';
}
