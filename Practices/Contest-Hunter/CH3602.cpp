// CH3602.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 200, mod = 1e9 + 9;
int T, n, arr[MAX_N], head[MAX_N], current, k, li[MAX_N], vis[MAX_N];
ll level[MAX_N], inv[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
int dfs(int u, int fa)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            if (vis[edges[i].to])
                return 1;
            return dfs(edges[i].to, u) + 1;
        }
    return 1;
}
ll quick_power(ll bas, ll tim)
{
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
ll Fn(int n) { return (n == 1) ? 1 : quick_power(n, n - 2); }
int main()
{
    scanf("%d", &T);
    level[0] = inv[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        level[i] = level[i - 1] * i % mod;
    inv[MAX_N - 1] = quick_power(level[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 1; i >= 2; i--)
        inv[i - 1] = inv[i] * i % mod;
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        memset(li, 0, sizeof(li)), k = 0;
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &arr[i]), addpath(arr[i], i), addpath(i, arr[i]);
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                li[++k] = dfs(i, 0);
        ll ans = 1;
        for (int i = 1; i <= k; i++)
            ans = ans * Fn(li[i]) % mod;
        ans = (ans * level[n - k] % mod);
        for (int i = 1; i <= k; i++)
            ans = ans * inv[li[i] - 1] % mod;
        printf("%lld\n", ans);
        continue;
    }
    return 0;
}