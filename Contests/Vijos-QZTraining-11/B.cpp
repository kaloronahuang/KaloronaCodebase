// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200100;

int head[MAX_N], current, deg[MAX_N], n, val[MAX_N], deletion[MAX_N], mem[MAX_N], sum[MAX_N], loop[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void toposort()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), deg[u]--;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (--deg[edges[i].to] == 0)
                q.push(edges[i].to);
    }
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0)
            loop[find(i)] += val[i];
}

void dfs(int u, int fat)
{
    if (deg[fat] <= 0)
        val[u] += val[fat];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat && deg[edges[i].to] <= 0)
            dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]), mem[i] = i, sum[i] = val[i];
    for (int i = 1, v; i <= n; i++)
    {
        scanf("%d", &v), addpath(i, v), addpath(v, i), deg[v]++;
        int x = find(i), y = find(v);
        if (x != y)
            mem[y] = x, sum[x] += sum[y];
    }
    toposort();
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0)
            dfs(i, 0);
    for (int i = 1; i <= n; i++)
        if (deg[i] > 0)
            printf("%d\n", loop[find(i)]);
        else
            printf("%d\n", val[i] + loop[find(i)]);
    return 0;
}