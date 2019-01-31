// P3388.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 20010, MAX_M = 100010;
int head[MAX_N], current, n, m, tmpx, tmpy, low[MAX_N], dfn[MAX_N], tot;
bool ans[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_M << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++tot;
    int child = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (!dfn[edges[i].to])
        {
            tarjan(edges[i].to, fa), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] >= dfn[u] && u != fa)
                ans[u] = true;
            if (u == fa)
                child++;
        }
        low[u] = min(low[u], dfn[edges[i].to]);
    }
    if (child >= 2 && u == fa)
        ans[u] = true;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    int cnt = 0;
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i, i);
    for (int i = 1; i <= n; i++)
        if (ans[i])
            cnt++;
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++)
        if (ans[i])
            printf("%d ", i);
    return 0;
}