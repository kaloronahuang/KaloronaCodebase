// BZ3294.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_C = 11, MAX_N = 31, mod = 1e9 + 9;

int n, m, c, ci[MAX_C], f[MAX_C][MAX_N][MAX_N], g[MAX_C][MAX_N][MAX_N], binomial[MAX_N * MAX_N][MAX_N * MAX_N];

int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= c; i++)
        scanf("%d", &ci[i]);
    binomial[0][0] = 1;
    for (int i = 1; i <= n * m; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    for (int k = 1; k <= c; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                g[k][i][j] = binomial[i * j][ci[k]];
                for (int a = 1; a <= i; a++)
                    for (int b = 1; b <= j; b++)
                        if (a != i || b != j)
                            g[k][i][j] = (0LL + g[k][i][j] + mod - 1LL * g[k][a][b] * binomial[i][a] % mod * binomial[j][b] % mod) % mod;
            }
    f[0][n][m] = 1;
    for (int k = 1; k <= c; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int a = i + 1; a <= n; a++)
                    for (int b = j + 1; b <= m; b++)
                        f[k][i][j] = (0LL + f[k][i][j] + 1LL * f[k - 1][a][b] * g[k][a - i][b - j] % mod * binomial[a][i] % mod * binomial[b][j] % mod) % mod;
    int ans = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            ans = (0LL + ans + f[c][i][j]) % mod;
    printf("%d\n", ans);
    return 0;
}