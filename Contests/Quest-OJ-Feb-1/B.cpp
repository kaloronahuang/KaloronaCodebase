// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e5 + 200, INF = 0x3f3f3f3f;
typedef long long ll;

int head[MAX_N], n, start_pt, end_pt, cur[MAX_N], dep[MAX_N], current, pi[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void addtube(int src, int dst, int flow)
{
    addpath(src, dst, flow), addpath(dst, src, 0);
}

bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(start_pt), dep[start_pt] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dep[edges[i].to] == 0)
                dep[edges[i].to] = dep[u] + 1, q.push(edges[i].to);
    }
    return dep[end_pt] != 0;
}

int dfs(int u, int flow)
{
    if (u == end_pt || flow == 0)
        return flow;
    for (int &i = cur[u]; i != -1; i = edges[i].nxt)
        if (edges[i].weight > 0 && dep[edges[i].to] == dep[u] + 1)
            if (int di = dfs(edges[i].to, min(flow, edges[i].weight)))
            {
                edges[i].weight -= di, edges[i ^ 1].weight += di;
                return di;
            }
    return 0;
}

ll dinic()
{
    ll ans = 0;
    while (bfs())
    {
        memcpy(cur, head, sizeof(cur));
        while (ll di = dfs(start_pt, INF))
            ans += di;
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n), start_pt = n + n + 1, end_pt = start_pt + 1;
    for (int i = 1, tot, target; i <= n; i++)
    {
        scanf("%d", &tot);
        while (tot--)
            scanf("%d", &target), addtube(i, target + n, INF);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]);
    for (int i = 1; i <= n; i++)
        addtube(i + n, end_pt, 5e6);
    for (int i = 1; i <= n; i++)
        addtube(start_pt, i, 5e6 - pi[i]), ans += 5e6 - pi[i];
    printf("%lld\n", dinic() - ans);
    return 0;
}