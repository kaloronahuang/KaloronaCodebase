// P2604.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 1010, MAX_M = 5050, INF = 0x3f3f3f3f;

int head[MAX_N], current, flow[MAX_N], dist[MAX_N], s, t, pre[MAX_N];
int n, m, k, ai[MAX_M], bi[MAX_M], ci[MAX_M], di[MAX_M];
bool vis[MAX_N];

struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 2];

void addpath(int src, int dst, int weight, int cst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cst;
    head[src] = current++;
}

void add(int src, int dst, int weight, int cst)
{
    addpath(src, dst, weight, cst);
    addpath(dst, src, 0, -cst);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(s), vis[s] = true;
    flow[s] = INF, dist[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                flow[edges[i].to] = min(flow[u], edges[i].weight);
                pre[edges[i].to] = i;
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[t] != INF;
}

pair<ll, ll> mcmf()
{
    ll ans1 = 0, ans2 = 0;
    while (spfa())
    {
        ans1 += flow[t], ans2 += flow[t] * dist[t];
        int pt = t, side = pre[pt];
        while (pt != s)
        {
            edges[side].weight -= flow[t], edges[side ^ 1].weight += flow[t];
            pt = edges[side ^ 1].to, side = pre[pt];
        }
    }
    return make_pair(ans1, ans2);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d%d", &ai[i], &bi[i], &ci[i], &di[i]);
    // first procedure:
    for (int i = 1; i <= m; i++)
        add(ai[i], bi[i], ci[i], 0);
    s = 1, t = n;
    pair<ll, ll> ans = mcmf();
    printf("%lld ", ans.first);
    // reset for the second procedure:
    for (int i = 1; i <= m; i++)
        add(ai[i], bi[i], INF, di[i]);
    s = 1, t = n + 1;
    add(n, t, k, 0);
    ans = mcmf();
    printf("%lld", ans.second);
    return 0;
}