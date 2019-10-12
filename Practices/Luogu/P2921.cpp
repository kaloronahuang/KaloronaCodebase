// P2921.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int aff[MAX_N], ncnt, answer[MAX_N], nxt[MAX_N], siz[MAX_N];
bool inst[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

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
        ncnt++;
        do
        {
            aff[stk[tail]] = ncnt, inst[stk[tail]] = false;
        } while (stk[tail--] != u);
    }
}

void jump(int u, int g_nxt, int step)
{
    if (answer[g_nxt] != 0)
    {
        answer[u] = answer[g_nxt] + step;
        return;
    }
    jump(u, nxt[g_nxt], step + 1);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &nxt[i]);
        addpath(i, nxt[i]);
        if (i == nxt[i])
            answer[i] = 1;
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 1; i <= n; i++)
        siz[aff[i]]++;
    for (int i = 1; i <= n; i++)
        if (siz[aff[i]] != 1)
            answer[i] = siz[aff[i]];
    for (int i = 1; i <= n; i++)
        if (answer[i] == 0)
            jump(i, nxt[i], 1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", answer[i]);
    return 0;
}