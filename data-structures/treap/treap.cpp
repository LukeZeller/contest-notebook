/*
* Description: treap
* Demo: insert/erase into sorted set, min and sum range query
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;

const int INF = 1231231234;

struct node
{
    int key, priority;
    node *l, *r;
    int sz, sum, minValue;

    node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL) {init(k);}
    void init(int k) {sz = 1, key = k, minValue = k, sum = k;} /*PS*/

    node* refresh() /*PS*/
    {
        init(key);
        sz += getSz(l) + getSz(r);
        if (l)
        {
            sum += l -> sum, minValue = min(minValue, l -> minValue);
        }
        if (r)
        {
            sum += r -> sum, minValue = min(minValue, r -> minValue);
        }
        return this;
    }

    static int getSz(node* &n){return n ? n -> sz : 0;}
};

struct treap //Careful!!! don't forget to call srand(time(0)) in main!
{
    node* root = NULL;

    pair <node*, node*> splitKey(node* curr, int key)
    {
        if (!curr) return {NULL, NULL};
        pair <node*, node*> res;
        if (curr -> key <= key)
        {
            tie(curr -> r, res.second) = splitKey(curr -> r, key);
            res.first = curr -> refresh();
        }
        else
        {
            tie(res.first, curr -> l) = splitKey(curr -> l, key);
            res.second = curr -> refresh();
        }
        return res;
    }

    pair <node*, node*> splitIndex(node* curr, int index)
    {
        if (!curr) return {NULL, NULL};
        pair <node*, node*> res;
        if (node::getSz(curr -> l) <= index)
        {
            tie(curr -> r, res.second) = splitIndex(curr -> r, index - node::getSz(curr -> l) - 1);
            res.first = curr -> refresh();
        }
        else
        {
            tie(res.first, curr -> l) = splitIndex(curr -> l, index);
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

    void insert(int k)
    {
        auto a = splitKey(root, k - 1), b = splitKey(a.second, k);
        b.first = new node(k);
        root = meld(a.first, root = meld(b.first, b.second));
    }

    void erase(int k)
    {
        auto a = splitKey(root, k - 1), b = splitKey(a.second, k);
        root = meld(a.first, b.second);
    }

    int query(int l, int r, bool isSumQuery) //PS: no bool if only 1 query type
    {
        auto a = splitIndex(root, l - 1), b = splitIndex(a.second, r - l);
        int res = isSumQuery ? b.first -> sum : b.first -> minValue; /*PS*/
        root = meld(a.first, root = meld(b.first, b.second));
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
