// CF891E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, k, ai[MAX_N], g[MAX_N], tmp[MAX_N];

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
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    g[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        memcpy(tmp, g, sizeof(tmp));
        // multiply the (ai[i] - x);
        // -x comes first;
        for (int j = 0; j < MAX_N; j++)
            tmp[j] = 1LL * g[j] * ai[i] % mod;
        for (int j = MAX_N - 1; j >= 1; j--)
            g[j] = 1LL * g[j - 1];
        g[0] = 0;
        for (int j = 0; j < MAX_N; j++)
            g[j] = (0LL + tmp[j] + mod - g[j]) % mod;
    }
    int ans = 1;
    for (int i = 1; i <= n; i++)
        ans = 1LL * ans * ai[i] % mod;
    int E = 0;
    for (int i = 0; i <= min(n, k); i++)
    {
        int tmp = 1LL * g[i] * quick_pow(quick_pow(n, i), mod - 2) % mod;
        for (int j = k; j >= k - i + 1; j--)
            tmp = 1LL * j * tmp % mod;
        E = (0LL + tmp + E) % mod;
    }
    printf("%lld\n", (0LL + ans + mod - E) % mod);
    return 0;
}