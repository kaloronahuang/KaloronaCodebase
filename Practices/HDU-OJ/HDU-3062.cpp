// HDU-3062.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 30000;
int head[MAX_N], current, n, m, tmp, st[MAX_N], cur, dfn[MAX_N], low[MAX_N], tot;
int color[MAX_N], ctot;
bool inst[MAX_N];
struct edge
{
    int to, nxt;
} edges[4000400];
void addpath(int u, int v)
{
    edges[current].to = v, edges[current].nxt = head[u];
    head[u] = current++;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++tot, inst[u] = true;
    st[++cur] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (!dfn[edges[i].to])
            tarjan(edges[i].to), low[u] = min(low[u], low[edges[i].to]);
        else if (inst[edges[i].to])
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u])
    {
        ctot++;
        do
        {
            inst[st[cur]] = false, color[st[cur]] = ctot;
        } while (u != st[cur--]);
    }
}
bool solve()
{
    for (int i = 0; i < 2 * n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 0; i < 2 * n; i += 2)
        if (color[i] == color[i + 1])
            return false;
    return true;
}
int main()
{
    while (~scanf("%d%d", &n, &m))
    {
        memset(head, -1, sizeof(head)), memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low)), memset(color, 0, sizeof(color));
        memset(st, 0, sizeof(st)), memset(inst, 0, sizeof(inst));
        for (int i = 1; i <= m; i++)
        {
            int a1, a2, c1, c2;
            scanf("%d%d%d%d", &a1, &a2, &c1, &c2);
            // reverse the relationship;
            addpath(2 * a1 + c1, 2 * a2 + 1 - c2);
            addpath(2 * a2 + c2, 2 * a1 + 1 - c1);
        }
        if (solve())
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}