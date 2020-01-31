// CF1294F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int head[MAX_N], n, current, pt, val, distA[MAX_N], distB[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa, int d)
{
    if (d > val)
        pt = u, val = d;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, d + 1);
}

void dfs2(int u, int fa, int d, int *dist)
{
    dist[u] = d;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs2(edges[i].to, u, d + 1, dist);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);

    int A, B, C, res = 0;
    dfs(1, 0, 0), A = pt, val = 0;
    dfs(A, 0, 0), B = pt, val = 0;

    dfs2(A, 0, 0, distA), dfs2(B, 0, 0, distB);
    for (int pt = 1; pt <= n; pt++)
        if (pt != A && pt != B && ((distA[B] + distA[pt] + distB[pt]) >> 1) > res)
            C = pt, res = ((distA[B] + distA[pt] + distB[pt]) >> 1);
    printf("%d\n%d %d %d\n", res, A, B, C);
    return 0;
}