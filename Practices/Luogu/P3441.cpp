// P3441.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 2000;

int head[MAX_N], current, n, l, dep[MAX_N], tot[MAX_N], deg[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &l);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 1)
            q.push(i), dep[i] = 1, tot[1]++;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] != 1 && (--deg[edges[i].to] == 1))
                dep[edges[i].to] = dep[u] + 1, tot[dep[edges[i].to]]++, q.push(edges[i].to);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += min(l << 1, tot[i]);
    printf("%d", ans);
    return 0;
}