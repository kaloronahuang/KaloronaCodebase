// P2153.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 550, MAX_M = 40100, INF = 0x3f3f3f3f;

int head[MAX_N], current, dist[MAX_N], flow[MAX_N], pre[MAX_N];
int s, t, n, m;
bool vis[MAX_N];
struct edge
{
    int to, nxt, weight, cost;
} edges[MAX_M << 1];

void addpath(int src, int dst, int weight, int cost)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].cost = cost, edges[current].nxt = head[src];
    head[src] = current++;
}

void add(int src, int dst, int weight, int cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist));
    queue<int> q;
    q.push(s), vis[s] = true, flow[s] = INF, dist[s] = 0;
    vis[1] = vis[n] = false;
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = false;
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (edges[i].weight > 0 && dist[edges[i].to] > dist[u] + edges[i].cost)
            {
                dist[edges[i].to] = dist[u] + edges[i].cost;
                pre[edges[i].to] = i, flow[edges[i].to] = min(flow[u], edges[i].weight);
                if (!vis[edges[i].to])
                    vis[edges[i].to] = true, q.push(edges[i].to);
            }
    }
    return dist[t] != INF;
}

pair<ll, ll> mfmc()
{
    ll ans1 = 0, ans2 = 0;
    while (spfa())
    {
        ans1 += flow[t], ans2 += dist[t] * flow[t];
        int u = t, i = pre[u];
        while (u != s)
        {
            edges[i].weight -= flow[t], edges[i ^ 1].weight += flow[t];
            u = edges[i ^ 1].to, i = pre[u];
        }
    }
    return make_pair(ans1, ans2);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    s = 1 + n, t = n;
    for (int i = 1; i <= n; i++)
        add(i, i + n, 1, 0);
    for (int i = 1, tmpx, tmpy, tmpz; i <= m; i++)
    {
        scanf("%d%d%d", &tmpx, &tmpy, &tmpz);
        add(tmpx + n, tmpy, 1, tmpz);
    }
    pair<ll, ll> ans = mfmc();
    printf("%lld %lld", ans.first, ans.second);
    return 0;
}