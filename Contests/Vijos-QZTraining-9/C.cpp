// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_L = 20;

int head[MAX_N], n, q, current, dep[MAX_N], fa[MAX_L][MAX_N], test_idx;

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
    q.push(1), dep[1] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].to != fa[0][u])
            {
                q.push(edges[i].to);
                fa[0][edges[i].to] = u, dep[edges[i].to] = dep[u] + 1;
            }
    }
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = MAX_L - 1; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = MAX_L - 1; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &q, &test_idx);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    bfs();
    for (int i = 1; i < MAX_L; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);

        // y -> lca1 & z -> y;
        int lca1 = getLCA(x, y), lca2 = getLCA(x, z), lca3 = getLCA(y, z);
        if (dep[lca2] > dep[lca1])
            lca1 = lca2;
        if (dep[lca3] > dep[lca1])
            lca1 = lca3;
        if (dep[lca1] == 0)
            printf("%d\n", dep[y] + 1);
        else
            printf("%d\n", dep[y] + dep[lca1] - 2 * dep[getLCA(y, lca1)] + 1);
    }
    return 0;
}