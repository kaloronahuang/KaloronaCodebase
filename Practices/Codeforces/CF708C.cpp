// CF708C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 400100;

int head[MAX_N], current, n, siz[MAX_N], dp[MAX_N][2], id[MAX_N], g[MAX_N], gsiz[MAX_N];
bool ans[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs_siz(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs_siz(edges[i].to, u), siz[u] += siz[edges[i].to];
            int term = (siz[edges[i].to] <= (n >> 1)) ? siz[edges[i].to] : dp[edges[i].to][0];
            if (term > dp[u][0])
                swap(dp[u][0], dp[u][1]), dp[u][0] = term, id[u] = edges[i].to;
            else if (term > dp[u][1])
                dp[u][1] = term;
        }
}

void dfs(int u, int fa)
{
    gsiz[u] = n - siz[u];
    int term = (gsiz[u] <= (n >> 1)) ? gsiz[u] : g[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            if (id[u] != edges[i].to)
                g[edges[i].to] = dp[u][0];
            else
                g[edges[i].to] = dp[u][1];
            g[edges[i].to] = max(g[edges[i].to], term);
            dfs(edges[i].to, u);
        }
}

void redfs(int u, int fa)
{
    bool pans = false, flag = true;
    if (gsiz[u] > (n >> 1))
        pans |= (gsiz[u] - g[u] <= (n >> 1)), flag = false;
    else
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa && siz[edges[i].to] > (n >> 1))
            {
                flag = false;
                pans |= ((siz[edges[i].to] - dp[edges[i].to][0]) <= (n >> 1));
                break;
            }
    pans |= flag;
    ans[u] = pans;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            redfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs_siz(1, 0), dfs(1, 0), redfs(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i] == true ? 1 : 0);
    return 0;
}