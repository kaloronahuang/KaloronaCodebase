// P2986.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], n, current;
ll ci[MAX_N], dp[MAX_N], answer = 0x3f3f3f3f3f3f3f3f, siz[MAX_N], f[MAX_N], sum;

struct edge
{
    int to, nxt;
    ll weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, ll weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void predfs(int u, int fa)
{
    siz[u] = ci[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            predfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            dp[u] += dp[edges[i].to] + 1LL * edges[i].weight * siz[edges[i].to];
        }
}

void dfs(int u, int fa)
{
    answer = min(answer, f[u]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            f[edges[i].to] = 1LL * f[u] - siz[edges[i].to] * edges[i].weight + (sum - siz[edges[i].to]) * edges[i].weight;
            dfs(edges[i].to, u);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ci[i]), sum += ci[i];
    for (ll i = 1, u, v, w; i <= n - 1; i++)
        scanf("%lld%lld%lld", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    predfs(1, 0);
    answer = min(answer, dp[1]), f[1] = dp[1];
    dfs(1, 0);
    printf("%lld", answer);
    return 0;
}