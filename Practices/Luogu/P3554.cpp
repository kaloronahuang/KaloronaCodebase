// P3554.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, head[MAX_N], current, dp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa, int mid)
{
    dp[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, mid), dp[u] += dp[edges[i].to] + 1;
    dp[u] = max(0, dp[u] - mid);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    if (n == 1)
        puts("0"), exit(0);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int l = 1, r = n - 1, res;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        dfs(1, 0, mid);
        if (dp[1] == 0)
            r = mid - 1, res = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}