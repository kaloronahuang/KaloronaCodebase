// CF1067B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, limit, head[MAX_N], current, deg[MAX_N], cnt[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void bfs()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!vis[i] && deg[i] == 1)
            q.push(i), vis[i] = true;
    if (q.empty())
        puts("No"), exit(0);
    memset(cnt, 0, sizeof(cnt));
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            --deg[edges[i].to], cnt[edges[i].to]++;
    }
    for (int i = 1; i <= n; i++)
        if (!vis[i] && cnt[i] > 0 && cnt[i] < 3)
            puts("No"), exit(0);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &limit);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= limit; i++)
        bfs();
    int valid = 0;
    for (int i = 1; i <= n; i++)
        valid += !vis[i];
    if (valid != 1)
        puts("No"), exit(0);
    puts("Yes");
    return 0;
}