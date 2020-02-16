// P5169.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_E = 3e5 + 200, MAX_B = 262144, mod = 998244353;

int head[MAX_N], current, n, m, q, bas[30], dist[MAX_N], dist_t[MAX_B], loop[MAX_B];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_E << 1];

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

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void insert(int x)
{
    for (int i = 20; i >= 0; i--)
        if (x & (1 << i))
            if (bas[i] == 0)
            {
                bas[i] = x;
                break;
            }
            else
                x ^= bas[i];
}

void prep(int dep, int pre)
{
    if (dep == 21)
        return (void)(loop[pre]++);
    prep(dep + 1, pre);
    if (bas[dep])
        prep(dep + 1, pre ^ bas[dep]);
}

void dfs(int u, int fa)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (vis[edges[i].to] == false)
            dist[edges[i].to] = dist[u] ^ edges[i].weight, dfs(edges[i].to, u);
        else
            insert(dist[edges[i].to] ^ dist[u] ^ edges[i].weight);
}

void fwt(int *arr, int opt)
{
    for (int step = 1; step < MAX_B; step <<= 1)
        for (int j = 0; j < MAX_B; j += (step << 1))
            for (int k = j; k < j + step; k++)
            {
                int A = arr[k], B = arr[k + step];
                arr[k] = (1LL * A + B) % mod, arr[k + step] = (1LL * A + mod - B) % mod;
                if (opt == -1)
                    arr[k] = 1LL * arr[k] * inv2 % mod, arr[k + step] = 1LL * arr[k + step] * inv2 % mod;
            }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0), prep(0, 0);
    for (int i = 1; i <= n; i++)
        dist_t[dist[i]]++;
    fwt(dist_t, 1), fwt(loop, 1);
    for (int i = 0; i < MAX_B; i++)
        loop[i] = 1LL * loop[i] * dist_t[i] % mod * dist_t[i] % mod;
    fwt(loop, -1);
    int x;
    while (q--)
        scanf("%d", &x), printf("%d\n", loop[x]);
    return 0;
}