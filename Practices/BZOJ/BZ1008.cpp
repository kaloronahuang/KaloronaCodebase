// BZ1008.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int mod = 100003;

ll m, n;

int quick_pow(ll bas, ll tim)
{
    int ret = 1;
    bas %= mod, tim %= (mod - 1);
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

int main()
{
    scanf("%lld%lld", &m, &n);
    m %= mod;
    int ret = 1LL * quick_pow(m - 1, n - 1) * m % mod;
    int ans = 1LL * quick_pow(m, n);
    printf("%d", (ans - ret + mod) % mod);
    return 0;
}