// LOJ6102.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 7;

int n, ki[MAX_N], fib[MAX_N], upper, g[MAX_N], cnt[MAX_N];

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
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ki[i]), upper = max(upper, ki[i]), cnt[ki[i]]++;
    g[1] = fib[1] = 1;
    for (int i = 2; i <= upper; i++)
        g[i] = fib[i] = (0LL + fib[i - 1] + fib[i - 2]) % mod;
    for (int i = 1; i <= upper; i++)
        for (int j = i << 1, inv = quick_pow(g[i], mod - 2); j <= upper; j += i)
            g[j] = 1LL * g[j] * inv % mod;
    int ans = 1;
    for (int i = 1; i <= upper; i++)
        for (int j = i; j <= upper; j += i)
            if (cnt[j])
            {
                ans = 1LL * ans * g[i] % mod;
                break;
            }
    printf("%d\n", ans);
    return 0;
}