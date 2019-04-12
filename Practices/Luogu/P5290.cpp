// P5290.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 2000;
int fa[MAX_N], head[MAX_N], current, weight[MAX_N], n, size[MAX_N];
int dfn[MAX_N], tot, tmp[MAX_N];
priority_queue<int> queues[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}
void dfs(int u)
{
    dfn[u] = ++tot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            dfs(edges[i].to);
            if (queues[dfn[edges[i].to]].size() > queues[dfn[u]].size())
                swap(dfn[edges[i].to], dfn[u]);
            int m = queues[dfn[edges[i].to]].size();
            for (int pt = 1; pt <= m; pt++)
            {
                tmp[pt] = max(queues[dfn[u]].top(),
                              queues[dfn[edges[i].to]].top());
                queues[dfn[edges[i].to]].pop();
                queues[dfn[u]].pop();
            }
            for (int pt = 1; pt <= m; pt++)
                queues[dfn[u]].push(tmp[pt]);
        }
    queues[dfn[u]].push(weight[u]);
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &weight[i]);
    for (int i = 2; i <= n; i++)
        scanf("%d", &fa[i]), addpath(fa[i], i), addpath(i, fa[i]);
    dfs(1);
    long long ans = 0;
    while (!queues[dfn[1]].empty())
        ans += queues[dfn[1]].top(), queues[dfn[1]].pop();
    printf("%lld", ans);
    return 0;
}