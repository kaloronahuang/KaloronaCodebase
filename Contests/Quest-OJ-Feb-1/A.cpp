// A.cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, mod, inv[int(5e5) + 20];

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
    scanf("%d%d%d", &n, &k, &mod);
    int ans = 1LL * quick_pow(n - k, k - 1) * quick_pow(k, n - k - 1) % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = (long long)(mod - mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= n - k; i++)
        ans = 1LL * ans * inv[i] % mod;
    for (int i = k; i <= n - 1; i++)
        ans = 1LL * ans * i % mod;
    printf("%d\n", ans);
    return 0;
}