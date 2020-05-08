// mooriokart.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1.5e3 + 200, mod = 1e9 + 7;

typedef long long ll;

int n, m, X, Y, head[MAX_N], current, dist[MAX_N][MAX_N], idx[MAX_N], mem[MAX_N];
int coltot, ans, prod[MAX_N][2600], tot[MAX_N][2600], F[2600][2], tmp[2600][2];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fa, int org, int dep)
{
    if (fa)
    {
        prod[idx[u]][min(dep, Y)] = (0LL + prod[idx[u]][min(dep, Y)] + dep) % mod;
        tot[idx[u]][min(dep, Y)]++;
    }
    dist[org][u] = dep;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, org, dep + edges[i].weight);
}

int main()
{
    // fileIO("mooriokart");
    memset(head, -1, sizeof(head)), memset(dist, -1, sizeof(dist));
    scanf("%d%d%d%d", &n, &m, &X, &Y);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
        if (find(u) != find(v))
            mem[find(u)] = find(v);
    }
    for (int i = 1; i <= n; i++)
    {
        if (idx[find(i)] == 0)
            idx[find(i)] = ++coltot;
        idx[i] = idx[find(i)];
    }
    for (int i = 1; i <= n; i++)
        dfs(i, 0, i, 0);
    int base = min(Y, coltot * X);
    F[base][0] = 1, F[base][1] = coltot * X;
    for (int i = 1; i <= coltot; i++)
    {
        for (int j = base; j <= Y; j++)
            tmp[j][0] = tmp[j][1] = 0;
        for (int j = 0; j <= Y; j++)
            if (tot[i][j])
                for (int k = base; k <= Y; k++)
                    if (F[k][0])
                    {
                        tmp[min(j + k, Y)][0] = (0LL + tmp[min(j + k, Y)][0] + 1LL * tot[i][j] * F[k][0] % mod) % mod;
                        tmp[min(j + k, Y)][1] = (0LL + tmp[min(j + k, Y)][1] + 1LL * prod[i][j] * F[k][0] % mod + 1LL * F[k][1] * tot[i][j] % mod) % mod;
                    }
        memcpy(F, tmp, sizeof(tmp));
    }
    ans = F[Y][1];
    for (int i = 1; i < coltot; i++)
        ans = 1LL * ans * i % mod;
    printf("%lld\n", 1LL * ans * ((mod + 1) >> 1) % mod);
    return 0;
}