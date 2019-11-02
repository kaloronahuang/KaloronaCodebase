// P4941.cpp
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 19;

int n, m, k;
ll ai[MAX_N], bi[MAX_N][MAX_N], dp[1 << MAX_N][MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    for (int i = 1, xi, yi, ci; i <= k; i++)
    {
        scanf("%d%d%d", &xi, &yi, &ci);
        if (xi == yi)
            ai[xi] += ci;
        else
            bi[xi][yi] += ci;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[1 << (i - 1)][i] = ai[i];
        if (m == 1)
            ans = max(ans, ai[i]);
    }
    for (int stat = 1; stat < (1 << n); stat++)
    {
        if (__builtin_popcount(stat) == 1)
            continue;
        for (int i = 0; i < n; i++)
            if (stat & (1 << i))
                for (int j = 0; j < n; j++)
                    if ((i != j) && (stat & (1 << j)))
                        dp[stat][i + 1] = max(dp[stat][i + 1], dp[stat ^ (1 << i)][j + 1] + ai[i + 1] + bi[j + 1][i + 1]);
        if (__builtin_popcount(stat) == m)
            for (int i = 0; i < n; i++)
                if (stat & (1 << i))
                    ans = max(ans, dp[stat][i + 1]);
    }
    printf("%lld", ans);
    return 0;
}