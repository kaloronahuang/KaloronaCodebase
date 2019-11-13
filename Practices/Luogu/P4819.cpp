// P4819.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100, MAX_E = 301000;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int aff[MAX_N], ncnt, siz[MAX_N], indeg[MAX_N];
bool inst[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_E << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u] && (++ncnt))
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false, siz[ncnt]++;
        } while (stk[tail--] != u);
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
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                G[aff[u]].push_back(aff[edges[i].to]), indeg[aff[edges[i].to]]++;
    bool flag = false;
    int tot = 0;
    for (int u = 1; u <= ncnt; u++)
    {
        if (!flag && indeg[u] == 0 && siz[u] == 1)
        {
            bool tag = false;
            for (int i = 0, siz = G[u].size(); i < siz; i++)
                if (indeg[G[u][i]] == 1)
                    tag = true;
            if (!tag)
                flag = true;
        }
        if (indeg[u] == 0)
            tot++;
    }
    if (flag)
        tot--;
    printf("%.6lf", 1.0 - double(tot) / double(n));
    return 0;
}