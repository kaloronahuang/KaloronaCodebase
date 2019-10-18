// P3119.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 2e6 + 200;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int aff[MAX_N], ncnt, siz[MAX_N], dist[MAX_N];
bool inst[MAX_N], vis[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

vector<int> G[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, inst[u] = true, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ncnt++;
        do
        {
            inst[stk[tail]] = false, aff[stk[tail]] = ncnt, siz[ncnt]++;
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 1; i <= ncnt; i++)
        siz[i + ncnt] = siz[i];
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[edges[i].to] != aff[u])
            {
                G[aff[u]].push_back(aff[edges[i].to]);
                G[aff[edges[i].to]].push_back(aff[u] + ncnt);
                G[aff[u] + ncnt].push_back(aff[edges[i].to] + ncnt);
            }
    queue<int> q;
    q.push(aff[1]), vis[aff[1]] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = 0, size = G[u].size(); i < size; i++)
            if (dist[G[u][i]] < dist[u] + siz[u])
            {
                dist[G[u][i]] = dist[u] + siz[u];
                if (vis[G[u][i]] == false)
                    q.push(G[u][i]), vis[G[u][i]] = true;
            }
    }
    printf("%d", dist[aff[1] + ncnt]);
    return 0;
}