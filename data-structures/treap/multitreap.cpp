/*
* Description: treap allowing duplicates
* Demo: insert/erase into sorted multiset, erase does nothing if element is not already in treap, inorder returns sorted elements of treap
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <random>

using namespace std;

struct node
{
    int key, priority, cnt;
    node *l, *r;
    int sz;

    node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL), cnt(1) {init(k);}
    void init(int k) {sz = cnt, key = k;}

    node* refresh()
    {
        init(key);
        sz += getSz(l) + getSz(r);
        return this;
    }

    void changeCount(int d){cnt += d, sz += d;}
    static int getSz(node* &n){return n ? n -> sz : 0;}
};

struct treap
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

    void inorder(node* &curr, vector <int> &res)
    {
        if (!curr) return;
        inorder(curr -> l, res);
        for (int i = 0; i < (curr -> cnt); i++)
            res.push_back(curr -> key);
        inorder(curr -> r, res);
    }

    vector <int> inorder()
    {
        vector <int> res;
        inorder(root, res);
        return res;
    }

    int size(){return node::getSz(root);}
};

int main()
{
    srand(time(0));

    treap trp;
    trp.insert(1), trp.insert(1), trp.insert(1);
    //Expected: 3
    cout<<trp.size()<<'\n';
    trp.erase(5), trp.insert(1), trp.insert(5), trp.insert(6), trp.insert(0);
    //Expected: 0 1 1 1 1 5 6
    for (int i: trp.inorder()) cout<<i<<" ";
    cout<<'\n';
    trp.erase(1), trp.erase(1), trp.erase(1), trp.erase(1), trp.erase(5), trp.erase(5), trp.erase(6), trp.erase(0);
    //Expected: 0
    cout<<trp.size()<<'\n';
    //Expected: [blank line]
    for (int i: trp.inorder()) cout<<i<<" ";
    cout<<'\n';

    return 0;
}
