// P2700.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100100;
const ll INF = 0x3f3f3f3f3f3f3f3fll;

int head[MAX_N], current, n, k;
ll dp[MAX_N][3];
bool tag[MAX_N], exist[MAX_N];

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

void dfs(int u, int fat)
{
    ll tot = 0;
    dp[u][0] = dp[u][1] = 0, exist[u] |= tag[u];
    if (exist[u])
        dp[u][0] = INF;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u), exist[u] |= exist[edges[i].to], tot += min(dp[edges[i].to][0], dp[edges[i].to][1] + edges[i].weight);
    if (tag[u] == false)
    {
        dp[u][1] = tot;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fat && exist[edges[i].to])
            {
                dp[u][1] = min(dp[u][1], tot - min(dp[edges[i].to][0], dp[edges[i].to][1] + edges[i].weight) + dp[edges[i].to][1]);
                if (tag[edges[i].to])
                    dp[u][0] += edges[i].weight + dp[edges[i].to][1];
                else
                    dp[u][0] += min(dp[edges[i].to][0], dp[edges[i].to][1] + edges[i].weight);
            }
    }
    else
    {
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fat && exist[edges[i].to])
                if (tag[edges[i].to])
                    dp[u][1] += edges[i].weight + dp[edges[i].to][1];
                else
                    dp[u][1] += min(dp[edges[i].to][0], dp[edges[i].to][1] + edges[i].weight);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1, tmp; i <= k; i++)
        scanf("%d", &tmp), tag[tmp + 1] = true;
    for (int i = 1, x, y, w; i <= n - 1; i++)
        scanf("%d%d%d", &x, &y, &w), addpath(x + 1, y + 1, w), addpath(y + 1, x + 1, w);
    dfs(1, 0);
    printf("%lld\n", min(dp[1][1], dp[1][0]));
    return 0;
}