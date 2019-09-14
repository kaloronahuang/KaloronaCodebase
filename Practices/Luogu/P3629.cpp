// P3629.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, k, dp[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs1(int u, int &ans)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to])
        {
            if ((dp[edges[i].to] = dp[u] + edges[i].weight) > dp[ans])
                ans = edges[i].to;
            dfs1(edges[i].to, ans);
        }
    vis[u] = false;
}

bool mark(int u, int fa, int dst)
{
    if (u == dst)
        return true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && mark(edges[i].to, u, dst))
        {
            edges[i].weight = -1, edges[i ^ 1].weight = -1;
            return true;
        }
    return false;
}

void doDp(int u, int &ans)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to])
        {
            doDp(edges[i].to, ans);
            ans = max(ans, dp[u] + dp[edges[i].to] + edges[i].weight);
            dp[u] = max(dp[u], dp[edges[i].to] + edges[i].weight);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1, x, y; i <= n - 1; i++)
        scanf("%d%d", &x, &y), addpath(x, y, 1), addpath(y, x, 1);
    int ans = 2 * (n - 1);
    int pt = 1, pt2;
    dfs1(1, pt);
    pt2 = pt, dp[pt] = 0;
    dfs1(pt, pt2);

    ans -= (dp[pt2] - 1);

    if (k == 1)
        printf("%d\n", ans), exit(0);
    else
    {
        memset(dp, 0, sizeof(dp));
        mark(pt, 0, pt2);
        pt2 = 0;
        doDp(pt, pt2);
        printf("%d\n", ans - (pt2 - 1));
    }

    return 0;
}