// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e7 + 200, mod = 1e9 + 7;

int n, m, task;

int quick_pow(int bas, int tim)
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

int main()
{
    scanf("%d%d%d", &n, &m, &task);
    int bas = 1, fac = 1, ifac = 1;
    for (int i = n + 1; i <= n + m + 1; i++)
        bas = 1LL * bas * i % mod;
    for (int i = 1; i <= m; i++)
        fac = 1LL * fac * i % mod;
    ifac = quick_pow(1LL * fac * (m + 1) % mod, mod - 2);
    bas = (0LL + mod + 1LL * bas * ifac % mod - 1) % mod;
    printf("%lld\n", 1LL * bas * fac % mod);
    return 0;
}