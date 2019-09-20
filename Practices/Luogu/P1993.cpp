// P1993.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 400010;

int head[MAX_N], current, n, m, dist[MAX_N];
bool vis[MAX_N], ans;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void dfs(int u)
{
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dist[edges[i].to] > dist[u] + edges[i].weight)
        {
            if (vis[edges[i].to] || ans)
            {
                ans = true;
                break;
            }
            dist[edges[i].to] = dist[u] + edges[i].weight;
            dfs(edges[i].to);
        }
    vis[u] = false;
}

int main()
{
    memset(head, -1, sizeof(head)), memset(dist, 0x3f, sizeof(dist));
    scanf("%d%d", &n, &m);
    for (int i = 1, opt, a, b, c; i <= m; i++)
    {
        scanf("%d%d%d", &opt, &a, &b);
        if (opt == 1)
            scanf("%d", &c), addpath(a, b, -c);
        else if (opt == 2)
            scanf("%d", &c), addpath(b, a, c);
        else
            addpath(a, b, 0), addpath(b, a, 0);
    }
    for (int i = 1; i <= n; i++)
    {
        dfs(i);
        if (ans)
            break;
    }
    if (ans)
        puts("No");
    else
        puts("Yes");
    return 0;
}