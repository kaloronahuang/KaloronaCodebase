// P1983.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

int head[MAX_N], current, n, m, dist[MAX_N], ptot, ans;
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    if (dist[u])
        return;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (dist[edges[i].to] == 0)
            dfs(edges[i].to);
        dist[u] = max(dist[u], dist[edges[i].to] + 1);
    }
    if (u > n)
        dist[u]--;
    ans = max(ans, dist[u]);
}

vector<int> vec;

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), ptot = n;
    for (int i = 1, si, tmp; i <= m; i++)
    {
        int pt = i + n;
        scanf("%d", &si);
        for (int j = 1; j <= si; j++)
            scanf("%d", &tmp), vec.push_back(tmp), vis[tmp] = true, addpath(pt, tmp);
        for (int j = vec[0]; j <= vec.back(); j++)
            if (!vis[j])
                addpath(j, pt);
        vec.clear();
        memset(vis, false, sizeof(vis));
    }
    ans = 1;
    for (int i = 1; i <= n; i++)
        if (dist[i] == 0)
            dfs(i);
    printf("%d", ans + 1);
    return 0;
}