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

    void pushLazy() /*PS*/
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

struct rope
{
    node* root;

    rope()
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
            a -> refresh();
            return a;
        }
        else
        {
            b -> l = meld(a, b -> l);
            b -> refresh();
            return b;
        }
    }

    int size(){return getSize(root);} /*PS*/
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
        root = NULL;
        for (int i = 0; i < n.size(); i++) root = meld(root, n[i]);
    }

    void insert(int p, int v) //PS: all following functions are independent
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

    void concat(rope &o)
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
    rope rp;
    string s = "hello";
    for (char c: s) rp.insert(rp.size(), c - 'a');

    //Expected: hel
    for (int i: rp.substr(0, 3)) cout<<char(i + 'a');
    cout<<'\n';

    rope rp2;
    string t = "world";
    for (char c: t) rp2.insert(rp2.size(), c - 'a');

    rp.concat(rp2);
    //Expected: helloworld
    for (int i: rp.substr(0, rp.size())) cout<<char(i + 'a');;
    cout<<'\n';

    rp.reverse(2, 4);
    //Expected: heollworld
    for (int i: rp.substr(0, rp.size())) cout<<char(i + 'a');;
    cout<<'\n';

    rp.erase(3, rp.size() - 3);
    rp.erase(0, 0);
    //Expected: eold
    for (int i: rp.substr(0, rp.size())) cout<<char(i + 'a');;
    cout<<'\n';

    return 0;
}
