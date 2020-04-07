// P3574.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200;

int n, ci[MAX_N], current, head[MAX_N], dp[MAX_N], siz[MAX_N];

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
    if (u != 1)
        dp[u] = ci[u];
    vector<int> sons;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), sons.push_back(edges[i].to);
    sort(sons.begin(), sons.end(), [](const int &rhs1, const int &rhs2) { return siz[rhs1] - dp[rhs1] < siz[rhs2] - dp[rhs2]; });
    for (int v : sons)
        dp[u] = max(dp[u], siz[u] + dp[v] + 1), siz[u] += siz[v] + 2;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ci[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), printf("%d\n", max(dp[1], siz[1] + ci[1]));
    return 0;
}