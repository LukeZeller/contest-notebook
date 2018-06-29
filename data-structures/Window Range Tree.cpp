/*
* Description: window range tree
* Demo: numBetween (Finds # of elements in [l, r] window with values in [k1, k2] range), replaceAt (change value at position i)
*       Can change numBetween to numLess/numGreater using respective treap functions
* Implementation: Uses fenwick tree with each node being a multi-treap
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <random>

using namespace std;

struct treap
{
    struct node
    {
        int key, priority, cnt;
        node *l, *r;
        int sz;

        node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL), cnt(1) {init(k);}
        void init(int k) {sz = cnt, key = k;}

        node* refresh()
        {
            sz = cnt;
            sz += getSz(l) + getSz(r);
            return this;
        }

        void changeCount(int d){cnt += d, sz += d;}
        static int getSz(node* &n){return n ? n -> sz : 0;}
    };

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
        if (b.first) b.first -> changeCount(1);
        else b.first = new node(k);
        root = meld(a.first, root = meld(b.first, b.second));
    }

    void erase(int k)
    {
        auto a = splitKey(root, k - 1), b = splitKey(a.second, k);
        if (!b.first) root = meld(a.first, b.second);
        else
        {
            if (b.first -> cnt > 0) b.first -> changeCount(-1);
            root = meld(a.first, root = meld(b.first, b.second));
        }
    }

    int numLess(int k, bool exclusive = true)
    {
        auto a = splitKey(root, k - exclusive);
        int res = node::getSz(a.first);
        root = meld(a.first, a.second);
        return res;
    }

    int numGreater(int k, bool exclusive = true)
    {
        auto a = splitKey(root, k + exclusive);
        int res = node::getSz(a.second);
        root = meld(a.first, a.second);
        return res;
    }

    int numBetween(int k1, int k2) // Note: between k1 and k2 inclusive
    {
        auto a = splitKey(root, k1 - 1), b = splitKey(a.second, k2);
        int res = node::getSz(b.first);
        root = meld(a.first, root = meld(b.first, b.second));
        return res;
    }
};

struct fenwickTree
{
    struct node : treap{}; //Caution!! Requires multiset treap

    vector <treap> elements;

    fenwickTree(vector <int> &v) //PS: can remove for-loop and initialize later
    {
        elements.resize(v.size() + 1);
        for (int i = 0; i < v.size(); i++) initAt(i, v[i]); //PS: see above
    }

    void initAt(int i, int v)
    {
        for (i++; i < elements.size(); i += i & (-i)) elements[i].insert(v);
    }

    void replaceAt(int i, int oldval, int newval)
    {
        for (i++; i < elements.size(); i += i & (-i))
        {
            elements[i].erase(oldval);
            elements[i].insert(newval);
        }
    }

    int numBetween(int i, int k1, int k2) //PS: can change to numLess/numGreater
    {
        int res = 0;
        for (i++; i > 0; i -= i & (-i)) res += elements[i].numBetween(k1, k2);
        return res;
    }

    int numBetween(int l, int r, int k1, int k2) {return numBetween(r, k1, k2) - numBetween(l - 1, k1, k2);} //PS: same as above
};

int main()
{
    srand(time(0));

    vector <int> v = {2, 5, 7, 13, 9, 12, 0, 20, 20, 20, -5};
    fenwickTree ft(v);

    //Expected: 2 (7, 9, 12, 13 are in [2, 5] interval -> 2 elements between 9 and 12 inclusive)
    cout<<ft.numBetween(2, 5, 9, 12)<<'\n';
    //Expected: 6
    cout<<ft.numBetween(0, v.size() - 1, 1, 19)<<'\n';
    //Expected: 2 3
    cout<<ft.numBetween(8, 9, 20, 20)<<" "<<ft.numBetween(0, v.size() - 1, 20, 20)<<'\n';
    ft.replaceAt(0, 2, -5);
    //Expected: 2
    cout<<ft.numBetween(0, v.size() - 1, -1000, -1)<<'\n';
    //Expected: 0 1
    cout<<ft.numBetween(0, 6, 20, 20)<<" "<<ft.numBetween(7, 7, 20, 20)<<'\n';

    return 0;
}
