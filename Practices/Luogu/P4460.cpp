// P4460.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21, mod = 1e8 + 7;

typedef long long ll;

int n, xi[MAX_N], yi[MAX_N], dp[1 << 20][MAX_N], trans[MAX_N][MAX_N];

ll getDist(int a, int b) { return 1LL * (xi[a] - xi[b]) * (xi[a] - xi[b]) + 1LL * (yi[a] - yi[b]) * (yi[a] - yi[b]); }

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
                for (int k = 1; k <= n; k++)
                    if (fabs(sqrt(getDist(i, j)) - (sqrt(getDist(i, k)) + sqrt(getDist(k, j)))) < 1e-8)
                        trans[i][j] |= (1 << (k - 1));
    for (int i = 1; i <= n; i++)
        dp[1 << (i - 1)][i] = 1;
    for (int stat = 0; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) >= 2)
            for (int i = 1; i <= n; i++)
                if (stat & (1 << (i - 1)))
                {
                    int pre = stat ^ (1 << (i - 1));
                    for (int j = 1; j <= n; j++)
                        if (pre & (1 << (j - 1)) && ((trans[j][i] & stat) == trans[j][i]))
                            dp[stat][i] = (0LL + dp[stat][i] + dp[pre][j]) % mod;
                }
    int ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) >= 4)
            for (int i = 1; i <= n; i++)
                if (stat & (1 << (i - 1)))
                    ans = (0LL + ans + dp[stat][i]) % mod;
    printf("%d\n", ans);
    return 0;
}