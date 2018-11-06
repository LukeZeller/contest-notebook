/*
* Description: permutation generation
* Demo: returns vector of (permutation, inversion count) pairs in order of least inversions to greatest inversions
*/

template <class T> using permutation_inversions = vector <pair<vector<T>, ll>>;
template <class T> permutation_inversions<T> permutations(const vector <T> &elements)
{
    if (elements.empty()) return {};
    else if (elements.size() == 1) return {{{elements[0]}, 0}};
    else
    {
        permutation_inversions <T> res;
        auto perm_invs = permutations(vector<T>(elements.begin() + 1, elements.end()));
        for (int i = 0; i <= perm_invs[0].first.size(); i++) for (const auto &pi: perm_invs)
        {
            auto temp = pi.first;
            temp.insert(temp.begin() + i, elements[0]);
            res.push_back(make_pair(temp, pi.second + i));
        }
        return res;
    }
}

int main()
{
    vector <int> elements = {1, 3, 5};
    int cnt = 0;
    // Expected: [0: 135], [1: 153], [1: 315], [2: 513], [2: 351], [3: 531]
    for (auto &perm: permutations(elements))
    {
        cout << "[" << perm.second << ": ";
        for (auto elem: perm.first)
            cout << elem;
        cout << "] ";
        cnt++;
    }
    // Expected: 6 permutations
    cout << cnt << " permutations" << endl;
}
