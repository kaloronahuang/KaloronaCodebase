// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, head[MAX_N], current, up[MAX_N];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int max_dist, pt;

void dfs(int u, int fa, int dep)
{
    if (max_dist < dep)
        pt = u, max_dist = dep;
    up[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, dep + 1);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int A, B;
    dfs(1, 0, 0), max_dist = 0, A = pt, dfs(pt, 0, 0), B = pt;
    if ((max_dist + 1) % 3 == 2)
        puts("Second");
    else
        puts("First");
    return 0;
}