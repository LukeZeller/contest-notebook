/*
* Description: base conversion functions
* Demo: from_istring(s, b) converts s (in base b) to its value in base 10 (long long)
*       to_istring(v, b) converts v (in base 10) to istring in base b
* Usage: If given non decimal number in base b (< 10), its value is from_string(to_istring(v, 10), b)
*        If base > 10, it needs to be parsed into an istring s, then can use from_string(s, b)
*/

typedef basic_string<int> istring;

ll from_istring(const istring &s, int base = 10)
{
    assert(!s.empty()); // PS: sometimes we're fine with empty strings - will return value 0
    ll pos = 1, res = 0;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        res += s[i] * pos;
        pos *= base;
    }
    return res;
}

istring to_istring(ll val, int base = 10)
{
    istring res;
    while (val)
    {
        res.push_back(val % base);
        val /= base;
    }
    reverse(res.begin(), res.end());
    return res.empty() ? istring{0} : res;
}
