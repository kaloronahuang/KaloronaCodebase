// P2341.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 90000;
struct edge
{
    int to, nxt;
} edges[MAX_N * 10];
int head[MAX_N], current, st[MAX_N], dfn[MAX_N], low[MAX_N], tot, affliate[MAX_N], cur, deg[MAX_N], n, m;
int tmpx, tmpy, ptot;
bool inst[MAX_N], vis[MAX_N];
void addpath(int src, int dst) { edges[current].to = dst, edges[current].nxt = head[src], head[src] = current++; }
void tarjan(int u)
{
    int v;
    dfn[u] = low[u] = ++tot, vis[u] = true;
    inst[u] = true, st[++cur] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!dfn[edges[i].to])
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int nw_pt = ++ptot;
        do
        {
            v = st[cur--];
            inst[v] = false;
            affliate[v] = nw_pt;
        } while (u != v);
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy);
    ptot = n;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            tarjan(i);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (affliate[u] != affliate[edges[i].to])
                addpath(affliate[u], affliate[edges[i].to]), deg[affliate[u]]++;
    int point, tim = 0;
    for (int u = n + 1; u <= ptot; u++)
        if (deg[u] == 0)
            point = u, tim++;
    if (tim > 1)
    {
        printf("0");
        return 0;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (affliate[i] == point)
            cnt++;
    printf("%d", cnt);
    return 0;
}