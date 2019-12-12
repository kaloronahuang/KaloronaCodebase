// CF1263F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int n[2], g, head[MAX_N], current, cost[2][MAX_N][MAX_N], li[2][MAX_N], ri[2][MAX_N], siz[MAX_N], dp[MAX_N];
vector<int> ls;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int typ, int u)
{
    if (u != 1)
        siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(typ, edges[i].to);
        li[typ][u] = min(li[typ][edges[i].to], li[typ][u]);
        ri[typ][u] = max(ri[typ][edges[i].to], ri[typ][u]);
        siz[u] += siz[edges[i].to];
    }
    int lft = li[typ][u], rig = ri[typ][u];
    cost[typ][lft][rig] = max(cost[typ][lft][rig], siz[u]);
}

int main()
{
    scanf("%d", &g);
    for (int typ = 0; typ < 2; typ++)
    {
        memset(head, -1, sizeof(head)), current = 0;
        memset(siz, 0, sizeof(siz));
        scanf("%d", &n[typ]);
        for (int i = 1; i <= n[typ]; i++)
            li[typ][i] = g + 1, ri[typ][i] = 0;
        for (int i = 2, fat; i <= n[typ]; i++)
            scanf("%d", &fat), addpath(fat, i);
        for (int i = 1, xi; i <= g; i++)
            scanf("%d", &xi), li[typ][xi] = ri[typ][xi] = i;
        dfs(typ, 1);
    }
    for (int i = 1; i <= g; i++)
        for (int j = i - 1; j >= 0; j--)
            dp[i] = max(dp[i], dp[j] + max(cost[0][j + 1][i], cost[1][j + 1][i]));
    printf("%d\n", dp[g]);
    return 0;
}