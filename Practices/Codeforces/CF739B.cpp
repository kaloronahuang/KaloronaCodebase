// CF739B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2e5 + 2000;

int head[MAX_N], current, fa[20][MAX_N], ai[MAX_N], n, ans[MAX_N];
ll dist[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u)
{
    for (int i = 1; i <= 19; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    int p = u;
    for (int i = 19; i >= 0; i--)
        if (dist[u] - dist[fa[i][p]] <= ai[u] && fa[i][p])
            p = fa[i][p];
    ans[fa[0][u]]++, ans[fa[0][p]]--;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        fa[0][edges[i].to] = u;
        dist[edges[i].to] = dist[u] + edges[i].weight;
        dfs(edges[i].to), ans[u] += ans[edges[i].to];
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 2, fat, w; i <= n; i++)
        scanf("%d%d", &fat, &w), addpath(fat, i, w);
    dfs(1);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    return 0;
}