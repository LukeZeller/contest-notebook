/* Description: Structure for finite field arithmetic
 */

long long MOD = 1000000007; /* PS */

struct ff_int {
    long long val;
    ff_int(long long val) : val(val) {}
    ff_int operator+ (const ff_int& o) const {return {(val + o.val) % MOD};}
    ff_int operator* (const ff_int& o) const {return {(val * o.val) % MOD};}
    ff_int operator^ (long long e) const {
        if (e == 0) return {1};
        if (e == 1) return *this;
        ff_int sqrtish = *this ^ (e / 2);
        return sqrtish * sqrtish * (*this ^ (e % 2));
    }
    ff_int operator/ (const ff_int& o) const {return *this * (o^(MOD - 2));}
    explicit operator int() {return val;}
};
