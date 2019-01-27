// P4069.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ls (p << 1)
#define rs ((p << 1) | 1)
#define mid ((l + r) >> 1)
using namespace std;
const int MAX_N = 100200, INF = 0x3f3f3f3f;
struct edge
{
    int to, nxt, w;
} edges[MAX_N << 1];
int head[MAX_N], n, m, current_edge, cnt;
int fa[MAX_N], dep[MAX_N], siz[MAX_N], son[MAX_N], dnf[MAX_N], antidnf[MAX_N];
int tree[MAX_N << 2];
struct line
{
    int a, b;
} lazy[MAX_N << 2];
void update(int ql, int qr, int l, int r, int p, line ln)
{
    if (ql <= l && r <= qr)
    {
        if (lazy[p].a != INF)
        {
            // merge;
        }
        else
        {
            tree[p] += ln.a * (l - r) * (l - r - 1) / 2 + ln.b + (l - r + 1);
            lazy[ls] = lazy[rs] = ln;
        }
        return;
    }
    if (lazy[p].a != INF)
    {
        lazy[p].a = INF;
    }
}
void addpath(int u, int v, int w)
{
    edges[current_edge].to = v, edges[current_edge].nxt = head[u];
    edges[current_edge].w = w, head[u] = current_edge++;
}
void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1;
    siz[u] = 1, dnf[u] = ++cnt, antidnf[dnf[u]] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (fa[u] == to)
            continue;
        dfs1(to);
        siz[u] += siz[to];
        if (siz[to] > siz[son[u]])
            son[u] = to;
    }
}
void dfs2(int u, int org)
{
    if (son[u] == 0)
        return;
    dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u] && edges[i].to != fa[u])
            dfs2(edges[i].to, edges[i].to);
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addpath(u, v, w), addpath(v, u, w);
    }
    return 0;
}