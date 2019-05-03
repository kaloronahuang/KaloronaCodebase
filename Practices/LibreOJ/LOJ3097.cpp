// LOJ3097.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX_N = 3030, INF = 0x3f3f3f3f3f3f3f3f;
ll head[MAX_N], current, dist[MAX_N], flow[MAX_N], tot, n, W, s, t, ai[MAX_N], pre[MAX_N];
int q[MAX_N];
struct edge
{
    ll to, nxt, weight, cost;
} edges[MAX_N * MAX_N];
bool vis[MAX_N];

void addpath(ll src, ll dst, ll weight, ll cost)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, edges[current].cost = cost;
    head[src] = current++;
}

void add(ll src, ll dst, ll weight, ll cost)
{
    addpath(src, dst, weight, cost);
    addpath(dst, src, 0, -cost);
}

bool spfa()
{
    memset(dist, 0x3f, sizeof(dist)), memset(vis, false, sizeof(vis));
    queue<ll> q;
    q.push(s), vis[s] = true, dist[s] = 0, flow[s] = INF;
    while (!q.empty())
    {
        ll u = q.front();
        q.pop(), vis[u] = false;
        for (ll i = head[u]; i != -1; i = edges[i].nxt)
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

ll mcmf()
{
    ll max_flow = 0, min_cost = 0;
    while (spfa())
    {
        ll p = t, i = pre[t];
        max_flow += flow[t], min_cost += flow[t] * dist[t];
        while (p != s)
        {
            edges[i].weight -= flow[t], edges[i ^ 1].weight += flow[t];
            p = edges[i ^ 1].to, i = pre[p];
        }
    }
    return min_cost;
}

void make_graph(int l, int r)
{
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    make_graph(l, mid), make_graph(mid + 1, r);
    int tt = 0;
    for (int i = l; i <= r; i++)
        q[++tt] = ai[i];
    sort(q + 1, q + 1 + tt);
    tt = unique(q + 1, q + t + 1) - q - 1;
    for (int i = 1; i < tt; i++)
    {
        add(tot + i, tot + i + 1, INF, abs(q[i + 1] - q[i]));
        add(tot + i + 1, tot + i, INF, abs(q[i + 1] - q[i]));
    }
    for (int i = l; i <= r; i++)
    {
        int d = (lower_bound(q + 1, q + 1 + tt, ai[i]) - q);
        if (i <= mid)
            add(tot + d, i + n, 1, 0);
        else
            add(i, tot + d, 1, 0);
    }
    tot += tt;
}

signed main()
{
    memset(head, -1, sizeof(head));
    scanf("%lld%lld", &n, &W);
    for (ll i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    s = 0, tot = t = 2 * n + 1;
    for (ll i = 1; i <= n; i++)
        add(s, i, 1, 0), add(i, t, 1, W), add(i + n, t, 1, 0);
    make_graph(1, n);
    printf("%lld", mcmf());
    return 0;
}