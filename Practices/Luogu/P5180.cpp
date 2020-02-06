// P5180.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_M = 3e5 + 200;

int phead[MAX_N], current, n, m, rhead[MAX_N], thead[MAX_N], dhead[MAX_N], ptot, dfn[MAX_N], anti[MAX_N], fa[MAX_N];
int mem[MAX_N], min_val[MAX_N], semi[MAX_N], dominator[MAX_N], siz[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_M << 3];

void addpath(int *head, int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x)
{
    if (x == mem[x])
        return x;
    int up = find(mem[x]);
    if (dfn[semi[min_val[mem[x]]]] < dfn[semi[min_val[x]]])
        min_val[x] = min_val[mem[x]];
    return mem[x] = up;
}

void dfs(int *head, int u)
{
    dfn[u] = ++ptot, anti[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            dfs(head, edges[i].to), fa[edges[i].to] = u;
}

void build()
{
    for (int idx = ptot; idx >= 2; idx--)
    {
        int u = anti[idx];
        for (int i = rhead[u]; i != -1; i = edges[i].nxt)
            if (dfn[edges[i].to] != 0)
            {
                find(edges[i].to);
                if (dfn[semi[min_val[edges[i].to]]] < dfn[semi[u]])
                    semi[u] = semi[min_val[edges[i].to]];
            }
        addpath(thead, semi[u], u);
        mem[u] = fa[u], u = fa[u];
        for (int i = thead[u]; i != -1; i = edges[i].nxt)
        {
            find(edges[i].to);
            if (semi[min_val[edges[i].to]] == u)
                dominator[edges[i].to] = u;
            else
                dominator[edges[i].to] = min_val[edges[i].to];
        }
    }
    for (int i = 2; i <= ptot; i++)
    {
        int u = anti[i];
        if (dominator[u] != semi[u])
            dominator[u] = dominator[dominator[u]];
    }
}

void calc(int u)
{
    siz[u] = 1;
    for (int i = dhead[u]; i != -1; i = edges[i].nxt)
        calc(edges[i].to), siz[u] += siz[edges[i].to];
}

int main()
{
    memset(phead, -1, sizeof(phead)), memset(rhead, -1, sizeof(rhead));
    memset(thead, -1, sizeof(thead)), memset(dhead, -1, sizeof(dhead));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(phead, u, v), addpath(rhead, v, u);
    dfs(phead, 1);
    for (int i = 1; i <= n; i++)
        mem[i] = min_val[i] = semi[i] = i;
    build();
    for (int i = 2; i <= n; i++)
        if (dominator[i])
            addpath(dhead, dominator[i], i);
    calc(1);
    for (int i = 1; i <= n; i++)
        printf("%d ", siz[i]);
    puts("");
    return 0;
}