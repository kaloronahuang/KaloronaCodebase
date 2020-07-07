// UOJ54.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 10007;

int T, mu[MAX_N], primes[MAX_N], tot, binomial[MAX_N][30], xpow[MAX_N][30];
int pre[MAX_N][30], g[MAX_N][30][30], mi[30], poly[30];
bool vis[MAX_N];

void preprocess()
{
    mu[1] = 1;
    for (int i = 2; i < MAX_N; i++)
    {
        if (!vis[i])
            primes[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1LL * i * primes[j] < MAX_N; j++)
        {
            vis[i * primes[j]] = true;
            if (i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            mu[i * primes[j]] = -mu[i];
        }
    }
    binomial[0][0] = 1;
    for (int i = 1; i < MAX_N; i++)
    {
        binomial[i][0] = binomial[i][i] = 1;
        for (int j = 1; j < i && j <= 20; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    for (int i = 0; i < MAX_N; i++)
    {
        xpow[i][0] = 1;
        for (int j = 1; j < 12; j++)
            xpow[i][j] = 1LL * xpow[i][j - 1] * i % mod;
    }
    for (int i = 1; i < MAX_N; i++)
        for (int j = 1; 1LL * i * j < MAX_N; j++)
            for (int k = 2; k <= 20; k++)
                pre[i * j][k] = (0LL + pre[i * j][k] + mod + 1LL * binomial[i - 1][k - 2] * mu[j] % mod) % mod;
    // g[prod][c][d];
    for (int i = 1; i < MAX_N; i++)
        for (int c = 2; c <= 20; c++)
            for (int d = 0; d < 12; d++)
                g[i][c][d] = (0LL + g[i][c][d] + g[i - 1][c][d] + 1LL * pre[i][c] * xpow[i][d] % mod) % mod;
}

int main()
{
    scanf("%d", &T), preprocess();
    // printf("%.4lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    while (T--)
    {
        int n, c, upper = 0x3f3f3f3f, ans = 0;
        scanf("%d%d", &n, &c);
        for (int i = 1; i <= n; i++)
            scanf("%d", &mi[i]), upper = min(upper, mi[i]);
        for (int i = 1, gx; i <= upper; i = gx + 1)
        {
            gx = upper;
            for (int j = 1; j <= n; j++)
                gx = min(gx, mi[j] / (mi[j] / i));
            memset(poly, 0, sizeof(poly)), poly[0] = 1;
            for (int j = 1; j <= n; j++)
            {
                int t = 1LL * mi[j] / i;
                int x = 1LL * t * mi[j] % mod;
                int y = mod - (1LL * t * (t + 1) >> 1) % mod;
                for (int k = n; k >= 1; k--)
                    poly[k] = (0LL + 1LL * poly[k] * x % mod + 1LL * poly[k - 1] * y % mod) % mod;
                poly[0] = 1LL * poly[0] * x % mod;
            }
            for (int j = 0; j <= n; j++)
            {
                ans = (0LL + ans + 1LL * poly[j] * ((0LL + g[gx][c][j] + mod - g[i - 1][c][j]) % mod) % mod) % mod;
                // printf("ANS for %d : %d -> %d %d %d %lld\n", T, i, gx, ans, poly[j], ((0LL + g[gx][c][j] + mod - g[i - 1][c][j]) % mod));
            }
        }
        printf("%d\n", ans);
        // printf("%.4lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
    }
    return 0;
}