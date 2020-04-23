// CF1332E.cpp
#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int fpow(int bas, long long tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

const int inv2 = fpow(2, mod - 2);

int main()
{
    int n, m, L, R;
    scanf("%d%d%d%d", &n, &m, &L, &R);
    int odd = (R >> 1) - ((L - 1) >> 1), even = R - L + 1 - odd;
    if ((1LL * n * m) & 1)
        printf("%d\n", fpow(R - L + 1, 1LL * n * m % (mod - 1)));
    else
        printf("%lld\n", 1LL * inv2 * ((0LL + fpow((0LL + odd + even) % mod, 1LL * n * m) + fpow(odd - even, 1LL * n * m)) % mod) % mod);
    return 0;
}