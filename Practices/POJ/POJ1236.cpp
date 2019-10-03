// POJ1236.cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 610;

int head[MAX_N], current, n, deg[MAX_N], dfn[MAX_N], stk[MAX_N], tail, low[MAX_N], odeg[MAX_N];
int ptot, ncnt, aff[MAX_N];
bool inst[MAX_N];
vector<int> G[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N * 400];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++, deg[dst]++, odeg[src]++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ptot;
    stk[++tail] = u, inst[u] = true;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        int color = ++ncnt;
        do
        {
            aff[stk[tail]] = color, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), ncnt = n;
    for (int i = 1, tmp; i <= n; i++)
        while (scanf("%d", &tmp) && tmp != 0)
            addpath(i, tmp), G[i].push_back(tmp);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        for (int j = 0, siz = G[i].size(); j < siz; j++)
        {
            int to = G[i][j];
            if (aff[i] != aff[to])
                addpath(aff[i], aff[to]);
        }
    int ans1 = 0, ans2 = 0;
    for (int i = n + 1; i <= ncnt; i++)
        if (deg[i] == 0)
            ans1++;
    for (int i = n + 1; i <= ncnt; i++)
        if (odeg[i] == 0)
            ans2++;
    if (ncnt == n + 1)
        ans2 = 0;
    else
        ans2 = max(ans2, ans1);
    printf("%d\n%d", ans1, ans2);
    return 0;
}