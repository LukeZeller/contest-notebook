/*
* Description: Enumerate all 3^n submasks of n-length bitmasks
* Demo: Breaks bitmask bm into all possible partition (sm1, sm2) pairs
* Usage: can also have "sm1 > bm ^ sm1" be inner-loop condition if s1/s2 used indistinguishably
*/

int submask_enumeration(int n)
{
    int cnt = 0;
    for (int bm = 0; bm < (1 << n); bm++)
    {
        for (int sm1 = bm; ; sm1 = (sm1 - 1) & bm)
        {
            int sm2 = bm ^ sm1;

            cnt++; /*PS*/

            if (sm1 == 0)
                break;
        }
    }
    return cnt;
}

int main()
{
    // Expected: 9 27 81
    cout << submask_enumeration(2) << " " << submask_enumeration(3) << " " << submask_enumeration(4) << '\n';
}
