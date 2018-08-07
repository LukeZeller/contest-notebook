// brute-force factorization, avoiding big integers by rearrangement
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=576&page=show_problem&problem=4105
// 2012 Mid-Central Regional

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true)
    {
        int a;
        cin>>a;

        if (a == 0) break;

        ll a_squared = (ll) a * a;

        int sol = 0;
        for (ll factor = 1; factor <= a; factor++)
        {
            if (a_squared % factor == 0)
            {
                ll o_factor = a_squared / factor;

                if ((o_factor + factor) % 2 != 0) continue; // c is (o_factor + factor)/2
                if ((o_factor - factor) % 2 != 0) continue; // b is (o_factor - factor)/2

                if (o_factor - factor > 2 * a)
                    sol++;
            }
        }
        cout<<sol<<'\n';
    }
    return 0;
}
