// UOJ554.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550;

int n, m, ai[10], head[MAX_N], current;
bool vis[MAX_N], tvis[MAX_N];
deque<int> path;

struct edge
{
    int to, nxt;
} edges[MAX_N * MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void output()
{
    printf("%lld\n", 1LL * path.size());
    for (int u : path)
        printf("%d ", u);
    puts(""), fflush(stdout);
}

void dfs(int u)
{
    path.push_back(u);
    if (path.size() >= 20 && tvis[path.size()] == false)
        output(), tvis[path.size()] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!vis[edges[i].to])
            vis[edges[i].to] = true, dfs(edges[i].to), vis[edges[i].to] = false;
    path.pop_back();
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 10; i++)
        scanf("%d", &ai[0]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v);
    for (int i = 1; i <= n; i++)
        vis[i] = true, dfs(i), vis[i] = false;
    return 0;
}