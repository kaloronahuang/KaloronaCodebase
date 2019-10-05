// POJ3678.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 3010, MAX_E = 1e6 + 200;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], ptot, stk[MAX_N], tail;
int aff[MAX_N], ncnt;
bool inst[MAX_N];
char opt[10];

struct edge
{
    int to, nxt;
} edges[MAX_E * 7];

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
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        scanf("%d%d%d%s", &u, &v, &w, opt + 1), u++, v++;
        if (opt[1] == 'A')
        {
            if (w == 0)
                addpath(u + n, v), addpath(v + n, u);
            else
                addpath(u, u + n), addpath(v, v + n);
        }
        else if (opt[1] == 'O')
        {
            if (w == 0)
                addpath(u + n, u), addpath(v + n, v);
            else
                addpath(u, v + n), addpath(v, u + n);
        }
        else
        {
            if (w == 0)
                addpath(u, v), addpath(u + n, v + n), addpath(v, u), addpath(v + n, u + n);
            else
                addpath(u, v + n), addpath(u + n, v), addpath(v + n, u), addpath(v, u + n);
        }
    }
    for (int i = 1; i <= (n << 1); i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 1; i <= (n << 1); i++)
        if (aff[i] == aff[i + n])
            puts("NO"), exit(0);
    puts("YES");
    return 0;
}