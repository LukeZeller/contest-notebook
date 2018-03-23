/*
* Description: rope (implicit treap w/ reversing)
* Demo: insert, erase range, reverse range, concat, substr
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <ctime>

using namespace std;

struct node
{
    int key, priority, sz;
    node *l, *r;
    bool rev; /*PS*/

    node(int k) : priority(rand() << 16 ^ rand()), l(NULL), r(NULL) {init(k), resetReverse();} //PS: remove rev if reverse() not used
    void init(int k){sz = 1, key = k;}

    node* refresh()
    {
        init(key);
        sz += getSz(l) + getSz(r);
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

    static int getSz(node* &n){return n ? n -> sz : 0;}
};

struct treap //Careful!!! don't forget to call srand(time(0)) in main!
{
    node* root = NULL;

    pair <node*, node*> splitIndex(node* curr, int index)
    {
        if (!curr) return {NULL, NULL};
        curr -> pushLazy(); /*PS*/
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
        if (a) a -> pushLazy(); /*PS*/
        if (b) b -> pushLazy(); /*PS*/
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

    int size(){return node::getSz(root);} //PS: all following functions are independent

    void insert(int p, int v)
    {
        auto a = splitIndex(root, p - 1);
        node* b = new node(v);
        root = meld(a.first, root = meld(b, a.second));
    }

    void erase(int l, int r)
    {
        auto a = splitIndex(root, l - 1), b = splitIndex(a.second, r - l);
        root = meld(a.first, b.second);
    }

    void concat(treap &o){root = meld(root, o.root);}

    void reverse(int l, int r) //[l, r] inclusive
    {
        auto a = splitIndex(root, l - 1), b = splitIndex(a.second, r - l);
        b.first -> setReverse();
        root = meld(a.first, root = meld(b.first, b.second));
    }

    vector <int> substr(int l, int len) //start at l, len chars long
    {
        auto a = splitIndex(root, l - 1), b = splitIndex(a.second, len - 1);
        vector <int> v;
        inorder(b.first, v);
        root = meld(a.first, root = meld(b.first, b.second));
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
    srand(time(0));

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
