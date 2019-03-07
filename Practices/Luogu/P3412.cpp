// P3412.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX_N = 101000, mod = 998244353;
ll n, siz[MAX_N], tmpx, tmpy, head[MAX_N], current, ans = 0;
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
ll quick_pow(ll bas, ll tim)
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
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (edges[i].to == fa)
            continue;
        dfs(edges[i].to, u);
        siz[u] += siz[edges[i].to];
    }
    ans = (ans + (2 * n - 2) * (siz[u]) % mod * (n - siz[u]) % mod) % mod;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs(1, 0);
    printf("%lld", 1LL * ans * quick_pow(1LL * n * n % mod, mod - 2) % mod);
    return 0;
}