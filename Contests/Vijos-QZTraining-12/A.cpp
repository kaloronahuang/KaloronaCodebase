// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050;

int head[MAX_N], current, n, k, dp[MAX_N][2];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), dp[u][0] += max(dp[edges[i].to][1], dp[edges[i].to][0]);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dp[u][1] = max(dp[u][1], dp[u][0] - max(dp[edges[i].to][1], dp[edges[i].to][0]) + dp[edges[i].to][0] + 1);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    int independent_set = max(dp[1][0], dp[1][1]);
    if ((independent_set << 1) < n || k < independent_set - 1)
        puts("policeman");
    else
        puts("arsonist");
    return 0;
}