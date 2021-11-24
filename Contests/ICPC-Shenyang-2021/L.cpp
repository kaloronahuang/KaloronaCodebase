// L.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5500;

int n, current, head[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = dst;
    head[src] = current++;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), n <<= 1;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    return 0;
}