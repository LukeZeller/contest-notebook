/*
* Description: rope (implicit treap w/ reversing)
* Demo: insert, erase range, reverse range, concat, substr
*/

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct node
{
    int key, priority, sz;
    node *l, *r;
    bool rev; /*PS*/

    node(int k) : key(k), priority(rand() << 16 ^ rand()), l(NULL), r(NULL), sz(1) {rev = false;} //PS: remove rev if reverse() not used

    node* refresh()
    {
        sz = 1;
        if (l) sz += l -> sz;
        if (r) sz += r -> sz;
        return this;
    }

    void pushLazy() //PS: see above
    {
        if (rev)
        {
            swap(l, r);
            if (l) l -> setReverse();
            if (r) r -> setReverse();
            resetReverse();
        }
    }

    void setReverse(){rev ^= true;} /*PS*/
    void resetReverse(){rev = false;} /*PS*/
};

struct treap
{
    node* root;

    treap()
    {
        root = NULL;
    }

    pair <node*, node*> splitIndex(node* curr, int index)
    {
        if (!curr) return {NULL, NULL};
        curr -> pushLazy(); /*PS*/
        pair <node*, node*> res;
        if (getSize(curr -> l) <= index)
        {
            tie(curr -> r, res.second) = splitIndex(curr -> r, index - getSize(curr -> l) - 1);
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
        if (a) a -> pushLazy(); /*PS*/
        if (b) b -> pushLazy(); /*PS*/
        if (!a or !b) return a ? a: b;
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

    vector<node*> splitRange(int l, int r)
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

    int size(){return getSize(root);} //PS: all following functions are independent/optional

    void insert(int p, int v)
    {
        vector <node*> n(3);
        n[1] = new node(v);
        tie(n[0], n[2]) = splitIndex(root, p - 1);
        meldRange(n);
    }

    void erase(int l, int r) //[l, r] inclusive
    {
        auto n = splitRange(l, r);
        root = meld(n[0], n[2]);
    }

    void concat(treap &o)
    {
        root = meld(root, o.root);
    }

    void reverse(int l, int r) //[l, r] inclusive
    {
        auto n = splitRange(l, r);
        n[1] -> setReverse();
        meldRange(n);
    }

    vector <int> substr(int l, int len) //start at l, len chars long
    {
        vector <int> v; //PS: can use string instead
        auto n = splitRange(l, l + len - 1);
        inorder(n[1], v);
        meldRange(n);
        return v;
    }

    void inorder(node* &curr, vector <int> &v)
    {
        if (!curr) return;
        curr -> pushLazy();
        inorder(curr -> l, v);
        v.push_back(curr -> key);
        inorder(curr -> r, v);
    }
};

int main()
{
    treap trp;
    string s = "hello";
    for (char c: s) trp.insert(trp.size(), c - 'a');

    //Expected: hel
    for (int i: trp.substr(0, 3)) cout<<char(i + 'a');
    cout<<'\n';

    treap trp2;
    string t = "world";
    for (char c: t) trp2.insert(trp2.size(), c - 'a');

    trp.concat(trp2);
    //Expected: helloworld
    for (int i: trp.substr(0, trp.size())) cout<<char(i + 'a');;
    cout<<'\n';

    trp.reverse(2, 4);
    //Expected: heollworld
    for (int i: trp.substr(0, trp.size())) cout<<char(i + 'a');;
    cout<<'\n';

    trp.erase(3, trp.size() - 3);
    trp.erase(0, 0);
    //Expected: eold
    for (int i: trp.substr(0, trp.size())) cout<<char(i + 'a');;
    cout<<'\n';
    
    return 0;
}
