// C.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 2000, mod = 1e9 + 7;
int head[MAX_N], current, n, tmpx, tmpy, tmpz;
int subtreeSiz[MAX_N], totTree, k;
bool vis[MAX_N];
struct edge
{
    int to, nxt, color;
} edges[MAX_N];
void addpath(int src, int dst, int color)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].color = color, head[src] = current++;
}
ll quick_pow(ll bas, ll tim)
{
    if (bas == 1)
        return 1;
    ll ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = ans * bas % mod;
        bas = bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}
void dfs(int u, int org, int fa)
{
    vis[u] = true;
    subtreeSiz[org]++;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, org, u);
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    bool flag = false;
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        if (tmpz != 1)
            addpath(tmpx, tmpy, tmpz), addpath(tmpy, tmpx, tmpz);
        else
            flag = true;
    }
    if (!flag)
        printf("0"), exit(0);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(i, ++totTree, 0);
    ll ans = quick_pow(n, k);
    for (int i = 1; i <= totTree; i++)
        ans = (ans - quick_pow(subtreeSiz[i], k) + mod) % mod;
    printf("%lld", ans);
    return 0;
}