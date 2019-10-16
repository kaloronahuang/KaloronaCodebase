// CF962F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], n, current, m, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N << 3], tail, ncnt;
bool inst[MAX_N];

set<int> node[MAX_N], eset[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            stk[++tail] = (i >> 1), stk[++tail] = u, stk[++tail] = edges[i].to;
            tarjan(edges[i].to, u);
            low[u] = min(low[u], low[edges[i].to]);
            if (dfn[u] <= low[edges[i].to])
            {
                ncnt++;
                while (true)
                {
                    int pt1 = stk[tail--], pt2 = stk[tail--], id = stk[tail--];
                    node[ncnt].insert(pt1), node[ncnt].insert(pt2);
                    eset[ncnt].insert(id);
                    if (pt1 == edges[i].to && pt2 == u)
                        break;
                }
            }
        }
        else if (edges[i].to != fa && dfn[edges[i].to] < dfn[u])
        {
            stk[++tail] = (i >> 1), stk[++tail] = u, stk[++tail] = edges[i].to;
            low[u] = min(low[u], dfn[edges[i].to]);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        addpath(u, v), addpath(v, u);
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0);
    set<int> ans;
    for (int i = 1; i <= ncnt; i++)
        if (node[i].size() == eset[i].size())
            ans.insert(eset[i].begin(), eset[i].end());
    printf("%d\n", ans.size());
    for (int u : ans)
        printf("%d ", u + 1);
    return 0;
}