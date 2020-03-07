// CF1083A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, current, head[MAX_N], wi[MAX_N];
ll dp[MAX_N], gans;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
    ll biggest = -1, sbiggest = -1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            ll tmp = dp[edges[i].to] - edges[i].weight;
            if (tmp > biggest)
                swap(biggest, sbiggest), biggest = tmp;
            else if (tmp > sbiggest)
                sbiggest = tmp;
        }
    dp[u] = wi[u];
    if (biggest != -1 && sbiggest != -1)
        gans = max(gans, wi[u] + biggest + sbiggest);
    if (biggest != -1)
        dp[u] += biggest;
    gans = max(gans, dp[u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]), gans = max(gans, 1LL * wi[i]);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0), printf("%lld\n", gans);
    return 0;
}