// P3007.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2300, MAX_E = 10100;

int head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail, ncnt;
int aff[MAX_N], n, m;
bool inst[MAX_N], vis[MAX_N];
char op1[10], op2[10], ans[MAX_E];
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
    if (dfn[u] == low[u])
    {
        int color = ++ncnt;
        do
        {
            aff[stk[tail]] = color, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

void dfs(int u)
{
    vis[u] = true;
    for (int i = 0, siz = G[u].size(); i < siz; i++)
        if (vis[G[u][i]] == false)
            dfs(G[u][i]);
}

bool check(int src)
{
    memset(vis, 0, sizeof(vis));
    dfs(src);
    for (int i = 1; i <= n; i++)
        if (vis[aff[i]] && vis[aff[i + n]])
            return false;
    return true;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, tmpx, tmpy; i <= m; i++)
    {
        scanf("%d%s%d%s", &tmpx, op1 + 1, &tmpy, op2 + 1);
        bool vote1 = op1[1] == 'Y', vote2 = op2[1] == 'Y';
        if (vote1)
            if (vote2)
                addpath(tmpx, tmpy + n), addpath(tmpy, tmpx + n);
            else
                addpath(tmpx, tmpy), addpath(tmpy + n, tmpx + n);
        else if (vote2)
            addpath(tmpx + n, tmpy + n), addpath(tmpy, tmpx);
        else
            addpath(tmpx + n, tmpy), addpath(tmpy + n, tmpx);
    }
    for (int i = 1; i <= (2 * n); i++)
        if (dfn[i] == 0)
            tarjan(i);
    // build graph;
    for (int u = 1; u <= 2 * n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                G[aff[u]].push_back(aff[edges[i].to]);
    for (int i = 1; i <= n; i++)
    {
        int pt1 = aff[i], pt2 = aff[i + n];
        bool c1 = check(pt1), c2 = check(pt2);
        if (!c1 && !c2)
            puts("IMPOSSIBLE"), exit(0);
        else if (c1 && !c2)
            ans[i] = 'N';
        else if (!c1 && c2)
            ans[i] = 'Y';
        else
            ans[i] = '?';
    }
    printf("%s", ans + 1);
    return 0;
}