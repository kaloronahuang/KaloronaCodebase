// D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int n, head[MAX_N], current, val[MAX_N], typ[MAX_N], ans[MAX_N];
char cmdlet[20];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs(edges[i].to, u);
        if (typ[u] == 1)
            val[u] &= val[edges[i].to];
        else if (typ[u] == 2)
            val[u] |= val[edges[i].to];
        else if (typ[u] == 3)
            val[u] ^= val[edges[i].to];
        else if (typ[u] == 4)
            val[u] = !val[edges[i].to];
    }
}

void dfs(int u, int fa, int flag)
{
    if (typ[u] == 5)
        ans[u] = flag ^ val[1];
    else if (typ[u] == 1)
    {
        int x = edges[head[u]].to, y = edges[edges[head[u]].nxt].to;
        if ((val[x] == 0 && val[y] == 0) || (val[x] == 1 && val[y] == 0))
            dfs(x, u, 0);
        else
            dfs(x, u, flag);
        if ((val[x] == 0 && val[y] == 0) || (val[x] == 0 && val[y] == 1))
            dfs(y, u, 0);
        else
            dfs(y, u, flag);
    }
    else if (typ[u] == 2)
    {
        int x = edges[head[u]].to, y = edges[edges[head[u]].nxt].to;
        if ((val[x] == 1 && val[y] == 1) || (val[x] == 0 && val[y] == 1))
            dfs(x, u, 0);
        else
            dfs(x, u, flag);
        if ((val[x] == 1 && val[y] == 1) || (val[x] == 1 && val[y] == 0))
            dfs(y, u, 0);
        else
            dfs(y, u, flag);
    }
    else if (typ[u] == 3)
    {
        int x = edges[head[u]].to, y = edges[edges[head[u]].nxt].to;
        dfs(x, u, flag), dfs(y, u, flag);
    }
    else
        dfs(edges[head[u]].to, u, flag);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++)
    {
        scanf("%s", cmdlet);
        if (cmdlet[0] == 'A')
            scanf("%d%d", &x, &y), addpath(i, x), addpath(i, y), typ[i] = 1, val[i] = 1;
        else if (cmdlet[0] == 'X')
            scanf("%d%d", &x, &y), addpath(i, x), addpath(i, y), typ[i] = 3;
        else if (cmdlet[0] == 'O')
            scanf("%d%d", &x, &y), addpath(i, x), addpath(i, y), typ[i] = 2;
        else if (cmdlet[0] == 'N')
            scanf("%d", &x), addpath(i, x), typ[i] = 4;
        else
            scanf("%d", &val[i]), typ[i] = 5;
    }
    dfs(1, 0), dfs(1, 0, 1);
    for (int i = 1; i <= n; i++)
        if (typ[i] == 5)
            printf("%d", ans[i]);
    return 0;
}