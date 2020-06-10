// BZ2560.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 16, mod = 1e9 + 7;

int n, ci[MAX_N][MAX_N], f[1 << MAX_N], g[1 << MAX_N];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &ci[i][j]);
    for (int stat = 1; stat < (1 << n); stat++)
    {
        g[stat] = 1;
        for (int i = 0; i < n; i++)
            if (stat & (1 << i))
                for (int j = i + 1; j < n; j++)
                    if (stat & (1 << j))
                        g[stat] = 1LL * g[stat] * (ci[i][j] + 1) % mod;
        f[stat] = g[stat];
        for (int sub = stat & (stat - 1); sub; sub = (stat & (stat - 1)) & (sub - 1))
            f[stat] = (0LL + f[stat] + mod - 1LL * g[sub] * f[stat ^ sub] % mod) % mod;
    }
    printf("%d\n", f[(1 << n) - 1]);
    return 0;
}