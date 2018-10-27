/*
* Description: monotone queue for sliding window min/max queries and insert (at back of window) / erase (from front of window) updates
* Demo: Takes in comparator op(a, b) which must return true iff a makes b redundant when a is after b in the sliding window
        Ex. op(a, b) -> return a < b makes it a min queue (ie. query() will return the current minimum in the queue)
*/

template <typename T, class Operation>
struct monotoneQueue
{
    int sz = 0;
    deque <T> elements;
    Operation op;

    monotoneQueue(Operation o) : op(o) {}

    void insert(T elem)
    {
        while (!elements.empty() and op(elem, elements.back()))
            elements.pop_back();
        elements.push_back(elem), sz++;
    }

    void erase(T elem)
    {
        if (elements.front() == elem)
            elements.pop_front();
        sz--;
    }

    T query() const {return elements.front();}
};

int main()
{
    auto cmp = [](int a, int b){return a < b;};
    monotoneQueue <int, decltype(cmp)> min_queue(cmp);

    int k = 3; // window length
    vector <int> a = {3, 5, 9, -1, 3, 4, 5, 2, 7, 8, 9}, mins;
    for (int i = 0; i < a.size(); i++)
    {
        min_queue.insert(a[i]);
        if (min_queue.sz == k)
        {
            mins.push_back(min_queue.query());
            min_queue.erase(a[i - k + 1]);
        }
    }
    // Expected: 3 -1 -1 -1 3 2 2 2 7
    for (int i: mins)
        cout << i << " ";
    cout << '\n';
}
