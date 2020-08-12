// P5369.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21, mod = 998244353;

int n, ai[MAX_N], dp[1 << MAX_N], g[1 << MAX_N], sum[1 << MAX_N], f[1 << MAX_N];

inline int lowbit(int x) { return x & (-x); }

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &sum[1 << i]), f[1 << i] = 1;
    for (int stat = 1; stat < (1 << n); stat++)
        sum[stat] = sum[stat ^ lowbit(stat)] + sum[lowbit(stat)];
    for (int stat = g[0] = 1; stat < (1 << n); stat++)
        if (sum[stat] >= 0)
        {
            for (int i = 0; i < n; i++)
                if (!(stat & (1 << i)))
                    f[stat | (1 << i)] = (0LL + f[stat | (1 << i)] + f[stat]) % mod;
        }
        else
            for (int i = 0; i < n; i++)
                if (stat & (1 << i))
                    g[stat] = (0LL + g[stat] + g[stat ^ (1 << i)]) % mod;
    int ans = 0;
    for (int stat = 1; stat < (1 << n); stat++)
        ans = (0LL + ans + 1LL * ((0LL + sum[stat] % mod + mod) % mod) * f[stat] % mod * g[((1 << n) - 1) ^ stat] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}