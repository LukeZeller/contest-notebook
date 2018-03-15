/*
* Description: point set tree
* Demo: findPoint (return id of point in rectangle), findAllPoints (return ids of all points in rectangle [output-sensitive runtime])
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct node : map<int, vector<int>> //PS: map<int, int> if not using findAllPoints()
{
    int findPoint(int l, int r)
    {
        auto it = lower_bound(l);
        if (it != end() and it -> first <= r)
        {
            return (it -> second)[0]; //PS: see above
        }
        else return -1;
    }
};

struct segmentTree
{
    int sz, offset;
    vector <node> elements;

    segmentTree(int ub, int lb) //ub is upper bound of positive x-values, lb is lower bound of negative x-values
    {
        ub = max(0, ub + 1), lb = min(0, lb - 1);
        sz = ub - lb + 1, offset = -lb;
        elements.resize(2 * sz);
    }

    void addPoint(int x, int y, int id)
    {
        x += offset;
        for(x += sz; x >= 1; x >>= 1)
        {
            elements[x][y].push_back(id); //elements[x][y] = id if not using findAllPoints()
        }
    }

    void correct(int &x1, int &y1, int &x2, int &y2) //PS: Only use if flipped/out-of-bound rectangles possible (ex. using dx/dy vectors)
    {
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        x1 = min(max(0, x1), sz - 1);
        x2 = min(max(0, x2), sz - 1);
    }

    int findPoint(int x1, int y1, int x2, int y2)
    {
        x1 += offset, x2 += offset;
        correct(x1, y1, x2, y2); /*PS*/

        for (x1 += sz, x2 += sz; x1 <= x2; ++x1 >>= 1, --x2 >>= 1)
        {
            if (x1 & 1)
            {
                int id = elements[x1].findPoint(y1, y2);
                if (id != -1) return id;
            }
            if(!(x2 & 1))
            {
                int id = elements[x2].findPoint(y1, y2);
                if (id != -1) return id;
            }
        }
        return -1;
    }

    vector <int> findAllPoints(int x1, int y1, int x2, int y2)
    {
        x1 += offset, x2 += offset;
        correct(x1, y1, x2, y2); /*PS*/

        vector <int> acc;
        for (x1 += sz, x2 += sz; x1 <= x2; ++x1 >>= 1, --x2 >>= 1)
        {
            if (x1 & 1)
            {
                for(auto it = elements[x1].lower_bound(y1); it != elements[x1].upper_bound(y2); it++)
                {
                    for (int id: (*it).second) acc.push_back(id);
                }
            }
            if(!(x2 & 1))
            {
                for(auto it = elements[x2].lower_bound(y1); it != elements[x2].upper_bound(y2); it++)
                {
                    for (int id: (*it).second) acc.push_back(id);
                }
            }
        }
        return acc;
    }
};

int main()
{
    segmentTree st(1000000, -1000000);

    st.addPoint(0, 0, 0);
    st.addPoint(-1, -2, 1);
    st.addPoint(-100, -3, 2);
    st.addPoint(1000000, 1000000, 3);
    st.addPoint(-1000000, -1000000, 4);

    //Expected: 2 1
    for (int i: st.findAllPoints(-100, -100, -1, -1)) cout<<i<<" ";
    cout<<'\n';

    //Expected: 0 1 2 3 4
    for (int i: st.findAllPoints(-1000000, -1000000, 1000000, 1000000)) cout<<i<<" ";
    cout<<'\n';

    //Expected: 2
    cout<<st.findPoint(-100, -3, -100, -3)<<'\n';

    return 0;
}
