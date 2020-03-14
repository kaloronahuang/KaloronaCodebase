// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550, mod = 1e9 + 7;

int n, fa[MAX_N], head[MAX_N], current, dp[MAX_N][MAX_N], coeff[MAX_N][MAX_N][MAX_N], sum[MAX_N][MAX_N << 1];
int siz[MAX_N], tmp[MAX_N], pre[MAX_N], dep[MAX_N][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    siz[u] = 1;
    int max_siz = 0;
    dep[u][1] = dep[fa[u]][1] + 1;
    for (int i = 2; i <= n; i++)
        dep[u][i] = 1LL * dep[u][i - 1] * dep[u][1] % mod;
    dep[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to);
    memset(tmp, 0, sizeof(tmp));
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        for (int a = 1; a <= max_siz; a++)
            for (int b = 1; b <= siz[edges[i].to]; b++)
                for (int k = 1; k <= a + b; k++)
                    dp[u][k] = (0LL + dp[u][k] + 1LL * tmp[a] * dp[edges[i].to][b] % mod * coeff[k][a][b] % mod * dep[u][a + b - k]) % mod;
        siz[u] += siz[edges[i].to], max_siz = max(max_siz, siz[edges[i].to]);
        for (int j = 1; j <= siz[edges[i].to]; j++)
            tmp[j] = (0LL + tmp[j] + dp[edges[i].to][j]) % mod;
    }
    if (head[u] == -1)
        dp[u][1] = 1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[i]), addpath(fa[i], i);
    coeff[0][0][0] = sum[0][0 + MAX_N] = 1;
    for (int k = 1; k <= n; k++)
        for (int i = 0; i <= n; i++)
            for (int j = 0; i + j <= n; j++)
            {
                coeff[k][i][j] = 2LL * sum[k - 1][i - j + MAX_N] % mod;
                coeff[k][i][j] = (0LL + coeff[k][i][j] + sum[k - 1][(i - 1) - j + MAX_N]) % mod;
                coeff[k][i][j] = (0LL + coeff[k][i][j] + sum[k - 1][i - (j - 1) + MAX_N]) % mod;
                sum[k][i - j + MAX_N] = (0LL + sum[k][i - j + MAX_N] + coeff[k][i][j]) % mod;
            }
    dfs(1), printf("%d\n", dp[1][1]);
    return 0;
}