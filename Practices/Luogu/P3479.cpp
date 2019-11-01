// P3479.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100, MAX_K = 22;

int head[MAX_N], current, n, m, limit;
long long f[MAX_N][MAX_K], g[MAX_N][MAX_K], ans;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    f[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int k = 0; k <= limit - 1; k++)
                f[u][k + 1] += f[edges[i].to][k];
            for (int k = limit; k >= 1; k--)
                g[u][k - 1] += g[edges[i].to][k];
        }
    int th_val = (f[u][limit] + m - 1) / m;
    ans += th_val;
    g[u][limit] += limit * m;
    for (int j = 0; j <= limit; j++)
        if (g[u][j] > 0)
            for (int k = j; k >= 0 && (k >= j - 1 || u == 1); k--)
            {
                if (g[u][j] <= f[u][k])
                {
                    f[u][k] -= g[u][j];
                    g[u][j] = 0;
                    break;
                }
                g[u][j] -= f[u][k];
                f[u][k] = 0;
            }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &limit);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    long long tot = 0;
    for (int i = 0; i <= limit; i++)
        tot += f[1][i];
    ans += (tot + m - 1) / m;
    printf("%lld", ans);
    return 0;
}