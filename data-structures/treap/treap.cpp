/*
* Description: treap
* Demo: insert/erase into sorted set, min and sum range query
*/

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct node
{
    int key, priority;
    node *l, *r;
    int sz, minValue, sum;

    node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL) {init(k);}
    void init(int k) {sz = 1, key = k, minValue = k, sum = k;} /*PS*/

    node* refresh() /*PS*/
    {
        init(key);
        if (l)
        {
            sz += l -> sz;
            minValue = min(minValue, l -> minValue), sum += l -> sum; /*PS*/
        }
        if (r)
        {
            sz += r -> sz;
            minValue = min(minValue, r -> minValue), sum += r -> sum; /*PS*/
        }
        return this;
    }
};

struct treap //Careful!!! don't forget to call srand(time(0)) in main!
{
    node* root;

    treap()
    {
        root = NULL;
    }

    bool branchRight(node* curr, int v, bool t)
    {
        return t ? curr -> key <= v : getSize(curr -> l) <= v;
    }

    int recurseRight(node* curr, int v, bool t)
    {
        return t ? v : v - getSize(curr -> l) - 1;
    }

    pair <node*, node*> splitKey(node* curr, int key){return splitBy(curr, key, true);}
    pair <node*, node*> splitIndex(node* curr, int index){return splitBy(curr, index, false);}

    pair <node*, node*> splitBy(node* curr, int v, bool t)
    {
        if (!curr) return {NULL, NULL};
        pair <node*, node*> res;
        if (branchRight(curr, v, t))
        {
            tie(curr -> r, res.second) = splitBy(curr -> r, recurseRight(curr, v, t), t);
            res.first = curr -> refresh();
        }
        else
        {
            tie(res.first, curr -> l) = splitBy(curr -> l, v, t);
            res.second = curr -> refresh();
        }
        return res;
    }

    node* meld(node* &a, node* &b)
    {
        if (!a or !b) return a ? a : b;
        if (a -> priority >= b -> priority)
        {
            a -> r = meld(a -> r, b);
            return a -> refresh();
        }
        else
        {
            b -> l = meld(a, b -> l);
            return b -> refresh();
        }
    }

    int getSize(node* &n){return n ? n -> sz : 0;}

    vector <node*> splitValue(int p)
    {
        vector <node*> n(3);
        tie(n[0], n[1]) = splitKey(root, p - 1);
        tie(n[1], n[2]) = splitKey(n[1], p);
        return n;
    }

    vector<node*> splitRange(int l, int r) //PS: Only for range queries
    {
        vector <node*> n(3);
        tie(n[0], n[1]) = splitIndex(root, l - 1);
        tie(n[1], n[2]) = splitIndex(n[1], r - l);
        return n;
    }

    void meldRange(vector <node*> &n)
    {
        root = meld(root = meld(n[0], n[1]), n[2]);
    }

    void insert(int k)
    {
        auto n = splitValue(k);
        n[1] = new node(k);
        meldRange(n);
    }

    void erase(int k)
    {
        auto n = splitValue(k);
        root = meld(n[0], n[2]);
    }

    int query(int l, int r, bool isSumQuery) //PS: no bool if only 1 query type
    {
        auto n = splitRange(l, r);
        int res = isSumQuery ? n[1] -> sum : n[1] -> minValue; /*PS*/
        meldRange(n);
        return res;
    }
};

int main()
{
    srand(time(0));

    treap trp;

    for (int i = 0; i < 5; i++) trp.insert(i);
    for (int i = 100; i >= 90; i--) trp.insert(i);

    //Expected: 1055
    cout<<trp.query(0, 15, true)<<'\n';

    trp.erase(90), trp.erase(91), trp.erase(92), trp.erase(93), trp.erase(94);
    //treap contains: 0 1 2 3 4 95 96 97 98 99 100

    //Expected: 99
    cout<<trp.query(4, 5, true)<<'\n';

    //Expected: 595
    cout<<trp.query(0, 10, true)<<'\n';

    //Expected: 0
    cout<<trp.query(0, 10, false)<<'\n';

    trp.erase(0);

    //Expected: 1 (bounds get clipped to valid range)
    cout<<trp.query(-100, 100, false)<<'\n';

    return 0;
}
