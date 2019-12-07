// BZ1006.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30010, MAX_E = 2000010;

int head[MAX_N], n, m, current, seq[MAX_N], deg[MAX_N], mark[MAX_N], color[MAX_N];
bool vis[MAX_N];

struct edge
{
    int from, to, nxt;
} edges[MAX_E];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].from = src, head[src] = current++;
}

void mcs()
{
    for (int i = 1; i <= n; i++)
        addpath(n + 1, i);
    int best = 0;
    for (int u = n; u >= 1; u--)
        while (true)
        {
            int target = 0;
            for (int i = head[best + 1 + n]; i != -1 && target == 0; i = edges[i].nxt)
                if (vis[edges[i].to] == false)
                    target = edges[i].to;
                else
                    head[best + 1 + n] = edges[i].nxt;
            if (target != 0)
            {
                vis[target] = true, seq[u] = target;
                for (int i = head[target]; i != -1; i = edges[i].nxt)
                    if (vis[edges[i].to] == false)
                    {
                        deg[edges[i].to]++, addpath(n + 1 + deg[edges[i].to], edges[i].to);
                        best = max(best, deg[edges[i].to]);
                    }
                break;
            }
            else
                best--;
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    mcs();
    int ans = 0;
    for (int idx = n; idx >= 1; idx--)
    {
        int u = seq[idx];
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            mark[color[edges[i].to]] = idx;
        for (color[u] = 1; color[u] <= n && mark[color[u]] == idx; color[u]++)
            ;
        ans = max(ans, color[u]);
    }
    printf("%d\n", ans);
    return 0;
}