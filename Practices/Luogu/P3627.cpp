// P3627.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#define pr pair<int, int>
using namespace std;
const int MX_N = 5000200;
int n, m, costs[MX_N], s, p, tmpx, tmpy;
int dfn[MX_N], low[MX_N], bcnt, cdfn, belong[MX_N], neocost[MX_N];
int dist[MX_N], deg[MX_N];
bool togsrc[MX_N], togdst[MX_N], inStack[MX_N], vis[MX_N];
stack<int> st;
int read()
{
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * w;
}
struct edge
{
    int from, to, nxt;
};
struct graph
{
    int head[MX_N], current;
    edge edges[MX_N << 1];
    graph() { memset(head, -1, sizeof(head)); }
    void addpath(int src, int dst)
    {
        edges[current].from = src;
        edges[current].to = dst, edges[current].nxt = head[src];
        head[src] = current++;
    }
} srcG, dstG;
void tarjan(int u)
{
    dfn[u] = low[u] = ++cdfn;
    inStack[u] = true, st.push(u);
    for (int i = srcG.head[u]; i != -1; i = srcG.edges[i].nxt)
        if (dfn[srcG.edges[i].to] == 0)
            tarjan(srcG.edges[i].to), low[u] = min(low[u], low[srcG.edges[i].to]);
        else if (inStack[srcG.edges[i].to])
            low[u] = min(low[u], dfn[srcG.edges[i].to]);
    if (low[u] == dfn[u])
    {
        bcnt++;
        while (true)
        {
            tmpx = st.top();
            st.pop();
            belong[tmpx] = bcnt, inStack[tmpx] = false;
            if (tmpx == u)
                break;
        }
    }
}
void buildmap()
{
    for (int i = 0; i <= srcG.current; i++)
    {
        int v = srcG.edges[i].to, u = srcG.edges[i].from;
        if (!belong[v] || !belong[u])
            continue;
        if (belong[u] == belong[v])
        {
            if (togsrc[u] || togsrc[v])
                togdst[belong[u]] = true;
        }
        else
        {
            dstG.addpath(belong[u], belong[v]);
            if (togsrc[u])
                togdst[belong[u]] = true;
            if (togsrc[v])
                togdst[belong[v]] = true;
            deg[belong[v]]++;
        }
    }
    for (int i = 1; i <= n; i++)
        neocost[belong[i]] += costs[i];
}
void dp(int pre)
{
    memset(dist, -0x3f, sizeof(dist));
    queue<int> q;
    q.push(pre), dist[pre] = neocost[pre];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = dstG.head[u]; i != -1; i = dstG.edges[i].nxt)
        {
            int to = dstG.edges[i].to;
            dist[to] = max(dist[to], dist[u] + neocost[to]);
            if (!(--deg[to]))
                q.push(to);
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), srcG.addpath(tmpx, tmpy);
    for (int i = 1; i <= n; i++)
        scanf("%d", &costs[i]);
    scanf("%d%d", &s, &p);
    for (int i = 1; i <= p; i++)
        scanf("%d", &tmpx), togsrc[tmpx] = true;
    tarjan(s);
    buildmap();
    dp(belong[s]);
    int ans = -1;
    for (int i = 1; i <= bcnt; i++)
        if (togdst[i])
            ans = max(ans, dist[i]);
    printf("%d", ans);
    return 0;
}