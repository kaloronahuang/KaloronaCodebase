// HDU-5909.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030, mod = 1e9 + 7;

int T, n, m, val[MAX_N], dp[MAX_N][MAX_N], ans[MAX_N], tmp[MAX_N], head[MAX_N], current, poly_siz;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

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

const int inv2 = quick_pow(2, mod - 2);

void fwt_xor(int *arr, int opt)
{
    for (int step = 1; step < poly_siz; step <<= 1)
        for (int j = 0; j < poly_siz; j += (step << 1))
            for (int k = j; k < j + step; k++)
            {
                int A = arr[k], B = arr[k + step];
                arr[k] = (1LL * A + B) % mod, arr[k + step] = (1LL * A + mod - B) % mod;
                if (opt == -1)
                    arr[k] = 1LL * arr[k] * inv2 % mod, arr[k + step] = 1LL * arr[k + step] * inv2 % mod;
            }
}

void dfs(int u, int fa)
{
    memset(dp[u], 0, sizeof(dp[u]));
    dp[u][val[u]]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            memcpy(tmp, dp[u], sizeof(tmp));
            fwt_xor(dp[u], 1), fwt_xor(dp[edges[i].to], 1);
            for (int j = 0; j < poly_siz; j++)
                dp[u][j] = 1LL * dp[u][j] * dp[edges[i].to][j] % mod;
            fwt_xor(dp[u], -1);
            for (int j = 0; j < poly_siz; j++)
                dp[u][j] = (0LL + dp[u][j] + tmp[j]) % mod;
        }
    for (int j = 0; j < poly_siz; j++)
        ans[j] = (0LL + ans[j] + dp[u][j]) % mod;
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(ans, 0, sizeof(ans));
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d", &val[i]);
        for (int i = 1, u, v; i <= n - 1; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
        poly_siz = 1;
        while (poly_siz <= m)
            poly_siz <<= 1;
        dfs(1, 0);
        for (int i = 0; i < m; i++)
            printf("%d%c", ans[i], i == m - 1 ? '\n' : ' ');
    }
    return 0;
}