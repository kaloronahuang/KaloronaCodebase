// POJ3585.cpp
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
const int MX_N = 210010;
int head[MX_N], current;
struct edge
{
    int to, w, nxt;
} edges[MX_N << 1];
int d[MX_N], f[MX_N], n, deg[MX_N];
bool vis[MX_N];
void addpath(int src, int dst, int w)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].w = w, head[src] = current++;
}
void dp(int u)
{
    d[u] = 0, vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (vis[to])
            continue;
        dp(to);
        if (deg[to] == 1)
            d[u] += edges[i].w;
        else
            d[u] += min(d[to], edges[i].w);
    }
}
void dfs(int u)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (vis[to])
            continue;
        if (deg[to] == 1)
            f[to] = d[to] + edges[i].w;
        else
            f[to] = d[to] + min(f[u] - min(d[to], edges[i].w), edges[i].w);
        dfs(to);
    }
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        current = 0;
        scanf("%d", &n);
        for (int i = 0; i <= n; i++)
            d[i] = f[i] = deg[i] = vis[i] = 0, head[i] = -1;
        for (int i = 1; i < n; i++)
        {
            int src, dst, w;
            scanf("%d%d%d", &src, &dst, &w);
            addpath(src, dst, w), addpath(dst, src, w);
            deg[src]++, deg[dst]++;
        }
        dp(1);
        for (int i = 1; i <= n; i++)
            vis[i] = false;
        f[1] = d[1];
        dfs(1);
        int ans = 0;
        for (int i = 1; i <= n; i++)
            ans = max(ans, f[i]);
        printf("%d\n", ans);
    }
    return 0;
}