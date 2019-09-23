// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330, INF = 0x3f3f3f3f;

int n, head[MAX_N], current, wi[MAX_N], ti[MAX_N], ans;
int f[MAX_N][MAX_N], g[MAX_N][MAX_N], h[MAX_N][MAX_N], T;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fat)
{
    for (int i = 0; i <= T; i++)
        f[u][i] = g[u][i] = h[u][i] = i >= ti[u] ? wi[u] : -INF;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
        {
            dfs(edges[i].to, u);
            for (int j = T; j >= edges[i].weight; j--)
                for (int k = 0; k < j - edges[i].weight + 1; k++)
                {
                    int pre_f = f[u][j], pre_g = g[u][j], pre_h = h[u][j];
                    if (j - k - 2 * edges[i].weight >= 0)
                    {
                        pre_f = max(pre_f, f[u][j - k - 2 * edges[i].weight] + f[edges[i].to][k]);
                        pre_g = max(pre_g, g[u][j - k - 2 * edges[i].weight] + f[edges[i].to][k]);
                        // different order;
                        pre_h = max(pre_h, h[u][j - k - 2 * edges[i].weight] + f[edges[i].to][k]);
                        pre_h = max(pre_h, f[u][j - k - 2 * edges[i].weight] + h[edges[i].to][k]);
                    }
                    pre_g = max(pre_g, f[u][j - k - edges[i].weight] + g[edges[i].to][k]);
                    pre_h = max(pre_h, g[u][j - k - edges[i].weight] + g[edges[i].to][k]);
                    f[u][j] = pre_f, g[u][j] = pre_g, h[u][j] = pre_h;
                }
        }
    ans = max(ans, h[u][T]);
}

int main()
{
    freopen("toyuq.in", "r", stdin);
    freopen("toyuq.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &T);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ti[i]);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0), printf("%d\n", ans);
    return 0;
}