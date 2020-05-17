// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 21, mod = 1e8 + 7;
const double eps = 1e-8;

int n, xi[MAX_N], yi[MAX_N], dp[1 << MAX_N][MAX_N], trans[MAX_N][MAX_N];

double getDist(int x, int y) { return sqrt(1LL * (xi[x] - xi[y]) * (xi[x] - xi[y]) + 1LL * (yi[x] - yi[y]) * (yi[x] - yi[y])); }

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &xi[i], &yi[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
            {
                int stat = 0;
                for (int k = 0; k < n; k++)
                    if (fabs(getDist(i, j) - getDist(i, k) - getDist(k, j)) < eps)
                        stat ^= (1 << k);
                trans[i][j] = stat;
            }
    for (int i = 0; i < n; i++)
        dp[1 << i][i] = 1;
    for (int stat = 0; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) >= 2)
        {
            for (int i = 0; i < n; i++)
                if (stat & (1 << i))
                {
                    int pre = stat ^ (1 << i);
                    for (int j = 0; j < n; j++)
                        if ((pre & (1 << j)) && (trans[i][j] & stat) == trans[i][j])
                            dp[stat][i] = (0LL + dp[stat][i] + dp[pre][j]) % mod;
                }
        }
    int ans = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        if (__builtin_popcount(stat) >= 4)
            for (int i = 0; i < n; i++)
                if (stat & (1 << i))
                    ans = (0LL + ans + dp[stat][i]) % mod;
    printf("%d\n", ans);
    return 0;
}