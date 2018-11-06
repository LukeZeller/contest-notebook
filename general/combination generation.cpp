/*
* Description: generating combinations
* Demo: combinations(e, k) returns list of all k-size combinations of elements from e (list is in lexicographical order if parameter e was sorted)
*/

template <typename T> void backtrack(vector <T> &curr, vector <vector<T>> &comb, const vector <T> &elements, int k, int prev = -1)
{
    if (curr.size() > k) assert(false);
    else if (curr.size() == k) comb.push_back(curr);
    else
    {
        for (int i = prev + 1; i < elements.size(); i++)
        {
            curr.push_back(elements[i]);
            backtrack(curr, comb, elements, k, i);
            curr.pop_back();
        }
    }
}

template <typename T> vector <vector<T>> combinations(const vector <T> &elements, int k)
{
    vector <T> curr;
    vector <vector<T>> res;
    backtrack(curr, res, elements, k);
    return res;
}

int main()
{
    vector <int> elements = {1, 3, 5, 7, 9};
    // Expeted: 135 137 139 157 159 179 357 359 379 579
    for (auto &comb: combinations(elements, 3))
    {
        for (auto elem: comb)
            cout << elem;
        cout << " ";
    }
    cout << '\n';
}
