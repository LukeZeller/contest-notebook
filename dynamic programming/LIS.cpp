/*
* Description: Longest increasing subsequence
* Demo: Returns length of LIS (LIS) or the subsequence itself (LIS_sol) given a lambda comparator cmp
*       Can change cmp to be <= for longest non-decreasing or to be > for longest decreasing
*/

// cmp is lambda (T a, T b) -> bool which returns true iff a can come before b in LIS
template <typename T, class Operation> int LIS(vector <T> &v, Operation cmp)
{
    vector <T> dp;
    for (auto elem: v)
    {
        int pos = lower_bound(dp.begin(), dp.end(), elem, cmp) - dp.begin();
        if (pos == dp.size())
            dp.push_back(elem);
        else
            dp[pos] = elem;
    }
    return dp.size();
}

// Assumes v's length is non-zero, see above for cmp
template <typename T, class Operation> vector <T> LIS_sol(vector <T> &v, Operation cmp)
{
    vector <T> dp;
    vector <int> ind, prev(v.size(), -1);
    for (int i = 0; i < v.size(); i++)
    {
        int pos = lower_bound(dp.begin(), dp.end(), v[i], cmp) - dp.begin();
        if (pos == dp.size())
        {
            dp.push_back(v[i]);
            ind.push_back(i);
        }
        else
        {
            dp[pos] = v[i];
            ind[pos] = i;
        }
        prev[i] = pos > 0 ? ind[pos - 1] : -1;
    }
    vector <T> sol;
    for (int curr = ind.back(); curr != -1; curr = prev[curr])
        sol.push_back(v[curr]); // PS: push_back(Curr) If you need indices instead of elements themselves
    reverse(sol.begin(), sol.end());
    return sol;
}

int main()
{
    vector <int> a = {1, 0, -1, 1, 1, 2, -2, 5};

    auto res1 = LIS_sol(a, [](int a, int b){return a < b;});
    auto res2 = LIS_sol(a, [](int a, int b){return a <= b;});
    auto res3 = LIS_sol(a, [](int a, int b){return a > b;});

    // Expected: -1 1 2 5
    for (int i: res1)
        cout << i << " ";
    cout << '\n';
    // Expected: -1 1 1 2 5
    for (int i: res2)
        cout << i << " ";
    cout << '\n';
    // Expected: 1 0 -1 -2
    for (int i: res3)
        cout << i << " ";
    cout << '\n';
}
